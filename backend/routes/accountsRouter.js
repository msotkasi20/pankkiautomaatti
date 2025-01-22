// routes/accountsRouter.js
import express from 'express';
import { getAllAccounts, getAccountsById, addAccounts, updateAccounts, deleteAccounts} from '../models/accountsModel.js';

const router = express.Router();

// Hakee kaikki tilit
router.get('/', async (req, res, next) => {
 try {
    const accounts = await getAllAccounts(req.pool);
    res.json({ success: true, data: accounts });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  }
});

// Hakee yksittäisen tilin ID:n perusteella
router.get('/:id', async (req, res, next) => {
  try {
    const accounts = await getAccountsById(req.pool, req.params.id);
    res.json({ success: true, data: accounts });
  } catch (error) {
    console.error(error.message);
    res.status(404).json({ success: false, error: error.message });
  }
});

// Luo uuden tilin
router.post('/', async (req, res) => {
  try {
    const newAccount = await addAccounts(req.pool, req.body);
    res.status(201).json(newAccount);
  } catch (error) {
    console.error(error.message);
    res.status(500).json({error: error.message});
  }
});

// Päivittää olemassa oleva tilin
router.put('/:id', async (req, res) => {
  try {
    const updatedAccount = await updateAccounts(req.pool, req.params.id, req.body);
    res.json(updatedAccount);
  } catch (error) {
    console.error(error.message);
    res.status(404).json({ error: error.message});
  }
});

// Poista tili
router.delete('/:id', async (req, res) => {
  try {
    await deleteAccounts(req.pool, req.params.id);
    res.json({ message: 'Account deleted successfully'});
  } catch (error) {
    res.status(404).json({ error: error.message });
  }
});

export default router;