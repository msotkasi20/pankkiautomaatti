// models/customerModel.js

// Hakee kaikki asiakkaat
export async function getAllCustomers(pool) {
  try {
      const [rows] = await pool.query('SELECT * FROM customer');
      return rows; // Palautetaan kaikki asiakkaat taulukkona
  } catch (error) {
      throw new Error(`Database error: ${error.message}`);
  }
}

// Hakee asiakkaan ID:n perusteella
export async function getCustomerById(pool, id) {
  try {
      const [rows] = await pool.query('SELECT * FROM customer WHERE idcustomer = ?', [id]);
      if (rows.length === 0) {
          throw new Error('Customer not found');
      }
      return rows[0];
  } catch (error) {
      throw new Error(`Database error: ${error.message}`);
  }
}

// Lisää uuden asiakkaan
export async function createCustomer(pool, customer) {
  try {
      const [rows] = await pool.query(
          'INSERT INTO customer (firstname, lastname, phone) VALUES (?, ?, ?)',
          [customer.firstname, customer.lastname, customer.phone]
      );
      return { idcustomer: rows.insertId, ...customer }; // Palautetaan luotu asiakas
  } catch (error) {
      throw new Error(`Database error: ${error.message}`);
  }
}

// Päivittää asiakkaan tiedot
export async function updateCustomer(pool, id, customer) {
  try {
      const [result] = await pool.query(
          'UPDATE customer SET firstname = ?, lastname = ?, phone = ? WHERE idcustomer = ?',
          [customer.firstname, customer.lastname, customer.phone, id]
      );
      if (result.affectedRows === 0) {
          throw new Error('Customer not found');
      }
      return { idcustomer: id, ...customer }; // Palautetaan päivitetty asiakas
  } catch (error) {
      throw new Error(`Database error: ${error.message}`);
  }
}

// Poistaa asiakkaan
export async function deleteCustomer(pool, id) {
  try {
      const [result] = await pool.query('DELETE FROM customer WHERE idcustomer = ?', [id]);
      if (result.affectedRows === 0) {
          throw new Error('Customer not found');
      }
      return { success: true };
  } catch (error) {
      throw new Error(`Database error: ${error.message}`);
  }
}