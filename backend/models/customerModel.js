// models/customerModel.js
export async function getAllCustomers(pool) {
    try {
      const [rows] = await pool.query('SELECT * FROM customer');
      return rows; // Palauttaa asiakkaat taulukkona
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }
  
  export async function getCustomerById(pool, id) {
    try {
      const [rows] = await pool.query('SELECT * FROM customer WHERE idCustomer = ?', [id]);
      if (rows.length === 0) {
        throw new Error('Customer not found');
      }
      return rows[0]; // Palauttaa yksittäisen asiakkaan
    } catch (error) {
      throw new Error(`Database error: ${error.message}`);
    }
  }
  