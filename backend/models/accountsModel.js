// models/customerModel.js
export async function getAllAccounts(pool) {
    try {
      const [rows] = await pool.query('SELECT * FROM accounts');
      return rows; // Palauttaa asiakkaat taulukkona
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }
  
  export async function getAccountsById(pool, id) {
    try {
      const [rows] = await pool.query('SELECT * FROM accounts WHERE idaccounts = ?', [id]);
      if (rows.length === 0) {
        throw new Error('Accounts not found');
      }
      return rows[0]; // Palauttaa yksittäisen asiakkaan
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }