import express from 'express';
const router = express.Router();

// GET all cards
router.get('/', async (req, res) => {
  // Logic to fetch all cards
  res.json({ message: 'Get all cards' });
});

// GET a single card by ID
router.get('/:id', async (req, res) => {
  const { id } = req.params;
  // Logic to fetch a card by ID
  res.json({ message: `Get card with ID: ${id}` });
});

export default router;