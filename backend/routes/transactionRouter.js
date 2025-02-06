// routes/tranactionRouter.js
import express from 'express';
import { 
  getAlltransaction, 
  getTransactionById,
  addTransaction,
  updateTransaction,
  deleteTransaction,
 } from '../models/transactionModel.js';
 import {
  getAccountsById,
  updateAccounts
 } from '../models/accountsModel.js';

const router = express.Router();

// Hakee kaikki transactiot
router.get('/', async (req, res, next) => {
  try {
    const transaction = await getAlltransaction(req.pool);
    res.json({ success: true, data: transaction });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  }
});

// Hakee yksittäisen transaction ID:n perusteella
router.get('/:id', async (req, res, next) => {
  try {
    const transaction = await getTransactionById(req.pool, req.params.id);
    res.json({ success: true, data: transaction });
  } catch (error) {
    console.error(error.message);
    res.status(404).json({ success: false, error: error.message });
  }
});

//luo uuden transaction
router.post('/', async (req, res) => {

  const {action, amount, idaccounts } = req.body;

  //tarkistetaan, että kaikki vaaditut kentät ovat läsnä
  if (!action || !amount || !idaccounts) {
    return res.status(400).json({
      success: false,
      message: 'Missing required fields: action, amount, idaccounts'
    });
  }
  try {
    const newTransaction = await addTransaction(req.pool, req.body);
    res.status(201).json(newTransaction); //palauttaa uuden transaction tiedot
  } catch (error) {
    console.error(error.message);
    res.status(500).json({error: error.message});
    
  }
});

//päivittää olemassa olevan transaction
router.put('/:id', async (req, res) => {

  const { action, actiontimestamp, amount, idaccounts } = req.body;

  if (!action || !actiontimestamp || !amount || !idaccounts) {
    return res.status(400).json({
      success: false,
      message: 'Missing required fields: action, actiontimestamp, amount, idaccounts'
    });
  }

  try {
    // Haetaan tilin tiedot tarkistusta varten
    const account = await getAccountsById(req.pool, idaccounts);
    if (!account) {
      return res.status(404).json({
        success: false,
        message: 'Account not found',
      });
    }

    // Tarkistetaan, onko tilillä tarpeeksi rahaa
    if (account.balance < amount) {
      return res.status(400).json({
        success: false,
        message: 'Insufficient balance for this withdrawal',
      });
    }

   // Lasketaan uusi saldo
   let newBalance = account.balance - amount;

   // Muodostetaan uusi tilitieto päivittämistä varten
   const updatedAccountData = {
     type: account.type,
     balance: newBalance, // Päivitetty saldo
     creditlimit: account.creditlimit,
     idcustomer: account.idcustomer
   };

   // Päivitetään koko tili, mutta vain saldo on muuttunut
   await updateAccounts(req.pool, idaccounts, updatedAccountData);


    // Päivitetään nosto transactioniin
    const updatedTransaction = await updateTransaction(req.pool, req.params.id, req.body);
    res.json({
      success: true,
      data: updatedTransaction,
    });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ error: error.message });
  }
});

//poistaa transaction

router.delete ('/:id', async (req, res) => {
  try {
    const message = await deleteTransaction(req.pool, req.params.id); //kutsuu modelin deleteTransaction funktiota
    res.json(message); //palauttaa poistoviestin
  } catch (error) {
    console.error(error.message);
    res.status(404),json({error: error.message});
  }
});
export default router;
