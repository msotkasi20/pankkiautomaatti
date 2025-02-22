// routes/tranactionRouter.js
import express from 'express';
import { 
  getAlltransaction, 
  getTransactionById,
  addTransaction,
  updateTransaction,
  deleteTransaction,
  getTransactionByAccountId,
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

// Hakee kaikki transaktiot tilin id:n perusteella
router.get('/byAccountId/:id', async (req, res, next) => {
  try {
    const transaction = await getTransactionByAccountId(req.pool, req.params.id);
    res.json({ success: true, data: transaction });
  } catch (error) {
    console.error(error.message);
    res.status(404).json({ success: false, error: error.message });
  }
});

//luo uuden transaction
router.post('/', async (req, res) => {

  const {amount, idaccounts } = req.body;

  //tarkistetaan, että kaikki vaaditut kentät ovat läsnä
  if (!amount || !idaccounts) {
    return res.status(400).json({
      success: false,
      message: 'Missing required fields: amount, idaccounts'
    });
  }
  
  try {
  // Haetaan tilin tiedot tarkistusta varten
  console.log(`Haetaan tilin tiedot tarkistusta varten id:llä ${idaccounts}`);
  const account = await getAccountsById(req.pool, idaccounts);
  if (!account) {
    return res.status(404).json({
      success: false,
      message: 'Account not found',
    });
  }

  // Tarkistetaan tilin tyyppi credit/debit
  if (account.type === 'credit') {

  // Tarkistetaan, onko tilillä tarpeeksi rahaa
  if (account.creditlimit < amount) {
    return res.status(400).json({
      success: false,
      message: 'Insufficient balance for this withdrawal',
    });
  }

   // Lasketaan uusi saldo
   let newCreditLimit = account.creditlimit - amount;
   console.log(`Uusi creditlimit: ${newCreditLimit}`);

   // Muodostetaan uusi tilitieto päivittämistä varten
   const updatedAccountData = {
     type: account.type,
     balance: account.balance,
     creditlimit: newCreditLimit, //Päivitetty creditlimit
     idcustomer: account.idcustomer
   };

   // Päivitetään koko tili, mutta vain saldo on muuttunut
   await updateAccounts(req.pool, idaccounts, updatedAccountData);

   const newTransaction = await addTransaction(req.pool, {
    amount: amount,
    idaccounts: idaccounts
   });

   res.json(newTransaction);

  } else if (account.type === 'debit') {
    // Tarkistetaan, onko tilillä tarpeeksi rahaa
    if (account.balance < amount) {
      return res.status(400).json({
        success: false,
        message: 'Insufficient balance for this withdrawal',
      }); 
    }

   // Lasketaan uusi saldo
   let newBalance = account.balance - amount;
   console.log(`Uusi balance: ${newBalance}`);

   // Muodostetaan uusi tilitieto päivittämistä varten
   const updatedAccountData = {
     type: account.type,
     balance: newBalance, //Päivitetty balance
     creditlimit: account.creditlimit,
     idcustomer: account.idcustomer
   };

   // Päivitetään koko tili, mutta vain saldo on muuttunut
   await updateAccounts(req.pool, idaccounts, updatedAccountData);

   const newTransaction = await addTransaction(req.pool, {
    amount: amount,
    idaccounts: idaccounts
   });

   res.json(newTransaction);
    }
  
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

//poistaa transactionin
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