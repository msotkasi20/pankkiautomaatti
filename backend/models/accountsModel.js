// models/customerModel.js
  export async function getAllAccounts(pool) {
    try {
      const [rows] = await pool.query('SELECT * FROM accounts');
      return rows; // Palauttaa tilit taulukkona
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
      return rows[0]; // Palauttaa yksittäisen tilin tiedot
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }

  export async function addAccounts(pool, accountsData) {
    try {
      const [result] = await pool.query('INSERT INTO accounts (type, balance, creditlimit, idcustomer) VALUES (?,?,?,?)', [accountsData.type, accountsData.balance, accountsData.creditlimit, accountsData.idcustomer]);
      return { id: result.insertId, ...accountsData}; // Palauttaa uuden tilin tiedot
    } catch (error) {
      throw new Error (`Database error: ${error.message}`);
    }
  }

  export async function updateAccounts(pool, id, accountsData) {
    try {
      const [result] = await pool.query('UPDATE accounts SET type=?, balance=?, creditlimit=?, idcustomer=? WHERE idaccounts=?', [accountsData.type, accountsData.balance, accountsData.creditlimit, accountsData.idcustomer, id]);
        if (result.affectedRows === 0) {
          throw new Error ('Account not found');
        }
        return { id, ...accountsData }; // Palauttaa päivitetyt tilitiedot
    } catch (error) {
  throw new Error (`Database error: ${error.message}`);
    }
  }

  export async function deleteAccounts(pool, id) {
    try {
      const [result] = await pool.query('DELETE FROM accounts WHERE idaccounts=?', [id]);
        if (result.affectedRows === 0) {
          throw new Error ('Account not found');
        }
        return { message: 'Account deleted successfully'}; // Palauttaa viestin onnistuneesta tilin poistosta
    } catch (error) {
      throw new Error (`Database error: ${error.message}`); 
    }
  }