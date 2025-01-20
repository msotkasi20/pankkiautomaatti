// routes/customerRouter.js
import express from 'express';
import { getAlltransaction, getTransactionById } from '../models/transactionModel.js';

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

export default router;
