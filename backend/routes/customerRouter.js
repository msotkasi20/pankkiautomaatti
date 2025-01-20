// routes/customerRouter.js
import express from 'express';
import { getAllCustomers, getCustomerById } from '../models/customerModel.js';

const router = express.Router();

// Hakee kaikki asiakkaat
router.get('/', async (req, res, next) => {
  try {
    const customers = await getAllCustomers(req.pool);
    res.json({ success: true, data: customers });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  }
});

// Hakee yksittäisen asiakkaan ID:n perusteella
router.get('/:id', async (req, res, next) => {
  try {
    const customer = await getCustomerById(req.pool, req.params.id);
    res.json({ success: true, data: customer });
  } catch (error) {
    console.error(error.message);
    res.status(404).json({ success: false, error: error.message });
  }
});

export default router;
