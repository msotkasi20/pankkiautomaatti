// models/transactionModel.js
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
  
  export async function addTransaction(pool, transactionData) {
    try {
      const [result] = await pool.query(
        'INSERT INTO transaction (action, actiontimestamp, amount, idaccounts) VALUES (?, ?, ?, ?)',
        [transactionData.action, transactionData.actiontimestamp, transactionData.amount, transactionData.idaccounts]
      );
      return { id: result.insertId, ...transactionData };
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
      
    }
  }

  export async function updateTransaction(pool, id, transactionData) {

    try {
      const [result]= await pool.query(
        'UPDATE transaction SET idaccounts = ?, amount = ?, action = ?, actiontimestamp = ? WHERE idtransaction = ?',
        [transactionData.idaccounts, transactionData.amount, transactionData.action, transactionData.actiontimestamp, id]
      );
      if (result.affectedRows === 0) {
        throw new Error ('Transaction not found');
      }
      return {id, ...transactionData};
    } catch (error) {
      throw new Error (`Database error: ${error.message}`);
      
    }
    
  }

  export async function deleteTransaction(pool, id) {
    try {
      const [result] = await pool.query('DELETE FROM transaction WHERE idtransaction = ?', [id] );
      if (result.affectedRows === 0) {
        throw new Error ('Transaction not found');
      }
      return {message: 'Transaction deleted succesfully'};
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
      
    }
  }

  export async function getAccountById(pool, idaccounts) {
    try {
      const [rows] = await pool.query('SELECT * FROM accounts WHERE idaccounts = ?', [idaccounts]);
      if (rows.length === 0) {
        throw new Error('Account not found');
      }
      return rows[0]; // Palauttaa yksittäisen tilin tiedot
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }
  