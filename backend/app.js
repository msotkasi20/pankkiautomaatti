import express from 'express';
import mysql from 'mysql2/promise';
import logger from 'morgan';
import customerRouter from './routes/customerRouter.js';
import accountsRouter from './routes/accountsRouter.js';
import accounts_cardsRouter from './routes/accounts_cardsRouter.js';
import cardRouter from './routes/cardRouter.js';
import transactionRouter from './routes/transactionRouter.js';
import loginRouter from './routes/login.js';
import dotenv from 'dotenv';
import path from 'path';
import { fileURLToPath } from 'url';

// Tiedostopolkujen määrittäminen
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Ladataan ympäristö muuttujat .env tiedostosta
dotenv.config({ path: path.resolve(__dirname, '.env') });

const app = express();

// Middleware
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.static(path.join(path.resolve(), 'public')));

// Määritetään tietokantayhteyksien pooli
const pool = mysql.createPool({
  host: process.env.DB_HOST,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  database: process.env.DB_NAME,
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});

// Tietokantayhteyden lisääminen pyyntöihin
app.use((req, res, next) => {
  req.pool = pool; // Lisätään tietokanta pool req. muuttujaan
  next();
});

// Routesit
app.use('/customer', customerRouter);
app.use('/accounts', accountsRouter);
app.use('/card', cardRouter);
app.use('/transaction', transactionRouter);
app.use('/login', loginRouter);
app.use('/accounts_cards', accounts_cardsRouter);

// Oletus virheenkäsittely
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).send('Something broke!');
});

// Sovelluksen vienti
export default app;