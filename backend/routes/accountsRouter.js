// routes/accountsRouter.js
import express from 'express';
import { getAllAccounts, getAccountsById } from '../models/accountsModel.js';

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

export default router;