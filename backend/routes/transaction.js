import express from 'express';
const router = express.Router();

// GET all transactions
router.get('/', async (req, res) => {
  // Logic to fetch all transactions
  res.json({ message: 'Get all transactions' });
});

export default router;