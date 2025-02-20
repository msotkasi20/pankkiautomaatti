import express from 'express';
import { getAllCards, getCardById } from '../models/cardModel.js';
import { createCard } from '../models/cardModel.js';
import { updateCard } from '../models/cardModel.js';
import { deleteCard } from '../models/cardModel.js';
import { updateCardLocked } from '../models/cardModel.js';  // Import the model function
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

// POST create a new card
router.post('/', async (req, res) => {
  try {
    console.log("Request body:", req.body); // Loggaa saapuva syöte

    // Tarkistetaan, että syöte sisältää 'type' ja 'cardpin'
    const { type, cardpin } = req.body;

    if (!type || !cardpin) {
      return res.status(400).json({
        success: false,
        error: "'type' and 'cardpin' are required fields",
      });
    }

    // Lisätään tarvittaessa tarkistus hyväksytyille ENUM-arvoille
    const validTypes = ['debit', 'credit', 'dual'];
    if (!validTypes.includes(type)) {
      return res.status(400).json({
        success: false,
        error: `'type' must be one of the following: ${validTypes.join(', ')}`,
      });
    }

    // Kutsutaan createCard-funktiota
    const card = await createCard(req.pool, { type, cardpin });

    // Palautetaan luodun kortin tiedot
    res.status(201).json({ success: true, data: card });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  }
});




// PUT update a card by ID

router.put('/:id', async (req, res) => {
  try{
    const updatedCard = await updateCard(req.pool, req.params.id, req.body);
    res.json({ success: true, data: updatedCard });
  } catch (error) {
    console.error(error.message);
    res.status(401).json({ success: false, error: error.message });
  }
});

// UPDATE only locked for login purposes

router.put('/:id/lock', async (req, res) => {
  try {
    if (req.body.locked === undefined) {
      return res.status(400).json({ success: false, error: "Locked status is required" });
    }

    const updatedCard = await updateCardLocked(req.pool, req.params.id, req.body.locked);

    res.json({ success: true, data: updatedCard });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  }
});


// DELETE a card by ID

router.delete('/:id', async (req, res) => {
  try{
    const card = await deleteCard(req.pool, req.params.id);
    res.json({ success: true, data: card });
  } catch (error) {
    console.error(error.message);
    res.status(400).json({ success: false, error: error.message });
  }

  });

export default router;