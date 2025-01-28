// routes/accountsRouter.js
import express from 'express';
import { getAllAccountsCards, getAccountsByCardAndType } from '../models/accounts_cardsModel.js';
const router = express.Router();

// Hakee kaikki korttien ja tilien tiedot
router.get('/', async (req, res, next) => {
 try {
    const accounts_cards = await getAllAccountsCards(req.pool);
    res.json({ success: true, data: accounts_cards });
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, error: error.message });
  }
});

// GET accounts by card ID and type
router.get('/by-card-and-type', async (req, res) => {
    const { idcard, type } = req.query;
    try {
      const accounts = await getAccountsByCardAndType(req.pool, idcard, type);
      res.json({ success: true, data: accounts });
    } catch (error) {
      console.error(error.message);
      res.status(500).json({ success: false, error: error.message });
    }
  });

export default router;
