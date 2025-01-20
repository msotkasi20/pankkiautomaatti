import express from 'express';
import mysql from 'mysql2/promise';
import logger from 'morgan';
import customerRouter from './routes/customerRouter.js';
import accountsRouter from './routes/accountsRouter.js';
import cardRouter from './routes/cardRouter.js';
import transactionRouter from './routes/transactionRouter.js';
import dotenv from 'dotenv';
import path from 'path';
import { fileURLToPath } from 'url';


const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Load environment variables from .env file
dotenv.config({ path: path.resolve(__dirname, '.env') });

const app = express();

// Middleware
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.static(path.join(path.resolve(), 'public')));



// Database connection pool
const pool = mysql.createPool({
  host: process.env.DB_HOST,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  database: process.env.DB_NAME,
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});

app.use((req, res, next) => {
  req.pool = pool; // Add the database pool to req object
  next();
});

// Routes
app.use('/customer', customerRouter);
app.use('/accounts', accountsRouter);
app.use('/cards', cardRouter);
app.use('/transaction', transactionRouter);

// Default error handler
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).send('Something broke!');
});

export default app;
