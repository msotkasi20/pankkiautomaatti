export async function getAllCards(pool) {
    try{
        const [rows] = await pool.query('SELECT * FROM card');
        return rows; // Palautetaan kaikki kortit taulukkona. 
    } catch (error) {
        throw new Error(`Database error: ${error.message}`);
    }   
}

export async function getCardById(pool, id) {
    try{
        const [rows] = await pool.query('SELECT * FROM card WHERE idcard = ?', [id]);
        if (rows.length == 0) {
            throw new Error('Card not found');

        }
        return rows[0];  
    } catch (error) {
        throw new Error(`Database error: ${error.message}`);
    }
}