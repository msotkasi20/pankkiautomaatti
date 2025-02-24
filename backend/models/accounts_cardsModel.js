export async function getAllAccountsCards(pool) {
    try {
      const [rows] = await pool.query('SELECT * FROM accounts_cards');
      return rows; // Palauttaa tilit ja kortit taulukkona
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }

  export async function getAccountsByCardAndType(pool, idcard, type) {
    try {
      const query = `
        SELECT a.*
        FROM accounts a
        JOIN accounts_cards ac ON a.idaccounts = ac.idaccounts
        WHERE ac.idcard = ? AND a.type = ?
      `;
      const [rows] = await pool.query(query, [idcard, type]);
      return rows; // Palauttaa tilit taulukkona
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }