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

export async function createCard(pool, card){
    try{
        const [rows] = await pool.query('INSERT INTO card (idcard, type, cardpin) VALUES (?, ?, ?)', [card.idcard, card.type, card.cardpin]);
        return rows; // Palauttaa luodun kortin
    } catch (error){
        throw new Error(`Database error: ${error.message}`);
    }
}

export async function updateCard(pool, id, card){
    try {
        const [rows] = await pool.query('UPDATE card SET type = ?, cardpin = ? WHERE idcard = ?', [card.type, card.cardpin, id]);
        if (rows.length == 0) {
            throw new Error('Card not found');

        }
        return rows[0];
    } catch (error){
        throw new Error(`Database error: ${error.message}`);
    }
}

export async function deleteCard(pool, id){
    try{
        const [rows] = await pool.query('DELETE FROM card WHERE idcard = ?', [id]);
        if (rows.length == 0) {
            throw new Error('Card not found');

        }
        return rows[0];
    } catch (error){
        throw new Error(`Database error: ${error.message}`);
    }
}