import express from 'express';

const router = express.Router();

router.get('/', async (req, res, next) => {
  try {
    const [rows] = await req.pool.query('SELECT * FROM customer');
    res.json({ success: true, data: rows });
  } catch (error) {
    console.error('Database error:', error);
    res.status(500).json({ success: false, error: error.message });
  }
});

export default router;
