// models/customerModel.js
export async function getAlltransaction(pool) {
    try {
      const [rows] = await pool.query('SELECT * FROM transaction');
      return rows; // Palauttaa transactiot taulukkona
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }
  
  export async function getTransactionById(pool, id) {
    try {
      const [rows] = await pool.query('SELECT * FROM transaction WHERE idtransaction = ?', [id]);
      if (rows.length === 0) {
        throw new Error('Transaction not found');
      }
      return rows[0]; // Palauttaa yksittäisen transaction
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }
  