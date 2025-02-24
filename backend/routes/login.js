import express from 'express';
import jwt from 'jsonwebtoken';
import bcrypt from 'bcryptjs';
import dotenv from 'dotenv';
import { getCardById } from '../models/cardModel.js'; // Tuodaan cardModel.js-tiedostosta getCardById-funktio

dotenv.config();
const router = express.Router();

router.post('/', async (req, res) => {
  const { idcard, cardpin } = req.body;

  // Tarkistetaan onko kortin ID tai PIN-koodi tyhjä
  if (!idcard || !cardpin) {
    console.log("Card ID or PIN missing");
    return res.status(400).json({ success: false, message: "Card ID or PIN missing" });
  }

  try {
    const card = await getCardById(req.pool, idcard);

    if (card) {

    //Tarkistetaan onko kortti lukittu
    if (card.locked) {
      console.log("Card is locked");
      return res.status(403).json({ success: false, message: "Card is locked" });
    }

    // Vertaillaan bcryptillä tallennettua PIN-koodia
    const isMatch = await bcrypt.compare(cardpin, card.cardpin);

    if (isMatch) {
      console.log("Login success");
      const token = generateAccessToken({ idcard });
      res.status(200).json({ success: true, token });
    } else {
      console.log("Invalid PIN");
      res.status(401).json({ success: false, message: "Invalid PIN" });
    }
    } else {
      console.log("Card not found");
      res.status(404).json({ success: false, message: "Card not found" });
    }
  } catch (error) {
    console.error(error.message);
    res.status(500).json({ success: false, message: "Internal server error" });
  }
});

// Funktio JWT-tunnuksen generointiin
function generateAccessToken(payload) {
  return jwt.sign(payload, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

export default router;