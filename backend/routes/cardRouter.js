import express from 'express';
import { getAllCards, getCardById } from '../models/cardModel.js';
const router = express.Router();

// GET all cards
router.get('/', async (req, res) => {
  try {
    const cards = await getAllCards(req.pool);
    res.json({ success: true, data: cards });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  // Logic to fetch all cards
  res.json({ message: 'Get all cards' });
}});

// GET a single card by ID
router.get('/:id', async (req, res) => {
  try {
    const card = await getCardById(req.pool, req.params.id);
    res.json({ success: true, data: card });
  } catch (error) {
    console.error(error.message);
    res.status(404).json({ success: false, error: error.message });
  const { id } = req.params;
  // Logic to fetch a card by ID
  res.json({ message: `Get card with ID: ${id}` });
}});

export default router;