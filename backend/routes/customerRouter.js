// routes/customerRouter.js
import express from 'express';
import { 
    getAllCustomers, 
    getCustomerById, 
    createCustomer, 
    updateCustomer, 
    deleteCustomer 
} from '../models/customerModel.js';

const router = express.Router();

// Hakee kaikki asiakkaat
router.get('/', async (req, res) => {
    try {
        const customers = await getAllCustomers(req.pool);
        res.json({ success: true, data: customers });
    } catch (error) {
        console.error(error.message);
        res.status(500).json({ success: false, error: error.message });
    }
});

// Hakee yksittäisen asiakkaan ID:n perusteella
router.get('/:id', async (req, res) => {
    try {
        const customer = await getCustomerById(req.pool, req.params.id);
        res.json({ success: true, data: customer });
    } catch (error) {
        console.error(error.message);
        res.status(404).json({ success: false, error: error.message });
    }
});

// Luo uuden asiakkaan
router.post('/', async (req, res) => {
    try {
        const newCustomer = await createCustomer(req.pool, req.body);
        res.status(201).json({ success: true, data: newCustomer });
    } catch (error) {
        console.error(error.message);
        res.status(400).json({ success: false, error: error.message });
    }
});

// Päivittää olemassa olevan asiakkaan tiedot
router.put('/:id', async (req, res) => {
    try {
        const updatedCustomer = await updateCustomer(req.pool, req.params.id, req.body);
        res.json({ success: true, data: updatedCustomer });
    } catch (error) {
        console.error(error.message);
        res.status(404).json({ success: false, error: error.message });
    }
});

// Poistaa asiakkaan ID:n perusteella
router.delete('/:id', async (req, res) => {
    try {
        const result = await deleteCustomer(req.pool, req.params.id);
        res.json({ success: true, data: result });
    } catch (error) {
        console.error(error.message);
        res.status(404).json({ success: false, error: error.message });
    }
});

export default router;
