import bcrypt from 'bcryptjs';

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
        if (rows.length === 0) {
            throw new Error('Card not found');

        }
        return rows[0];  
    } catch (error) {
        throw new Error(`Database error: ${error.message}`);
    }
}

export async function encryptCardPin(cardpin) {
    try {
      const salt = await bcrypt.genSalt(10);
      const hashedPin = await bcrypt.hash(cardpin, salt);
      return hashedPin;
    } catch (error) {
      throw new Error(`Encryption error: ${error.message}`);
    }
  }

    // Luodaan kortti tietokantaan, PIN-koodin kryptaus
    
    export async function createCard(pool, card) {
        try {
          console.log("Received card object:", card); // Loggaa kortin tiedot
      
          if (!card.cardpin) {
            throw new Error('PIN is missing');
          }
          
          const pinAsString = String(card.cardpin);
      
          // Kryptataan PIN ennen tallentamista
          const hashedPin = await encryptCardPin(pinAsString);
      
          // Lisää uusi kortti ilman id:tä
          const [rows] = await pool.query(
            'INSERT INTO card (type, cardpin) VALUES (?, ?)',
            [card.type, hashedPin]
          );
      
          // Palautetaan luodun kortin tiedot
          return { idcard: rows.insertId, type: card.type };
        } catch (error) {
          throw new Error(`Database error: ${error.message}`);
        }
      }
      
      

export async function updateCard(pool, id, card){
    try {
        const [rows] = await pool.query('UPDATE card SET type = ?, cardpin = ? WHERE idcard = ?', [card.type, card.cardpin, id]);
        if (rows.length === 0) {
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
        if (rows.length === 0) {
            throw new Error('Card not found');

        }
        return rows[0];
    } catch (error){
        throw new Error(`Database error: ${error.message}`);
    }
}