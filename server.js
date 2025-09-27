const express = require('express');
const { execFile } = require('child_process');
const path = require('path');

const app = express();
// Parse JSON bodies
app.use(express.json());

// Parse URL-encoded bodies (optional, for forms)
app.use(express.urlencoded({ extended: true }));

// Serve frontend
app.use(express.static(path.join(__dirname, 'Frontend')));

// Handle POST request to backend (C++)
app.post('/users', (req, res) => {
  const { name, weight, gender } = req.body;

  // Call the compiled C++ program
  execFile(path.join(__dirname, 'Backend/output', process.platform === 'win32' ? 'user.exe' : 'user'),
   [name, weight, gender], (error, stdout, stderr) => {
    if (error) {
      console.error('Error executing C++:', error);
      return res.status(500).send('Error running C++ program');
    }
    try {
      const data = JSON.parse(stdout);
      res.json(data);
    } catch (err) {
      console.error('Failed to parse C++ output:', err, stdout);
      res.status(500).send('Invalid C++ output');
    }
  });
});

// Default route -> serve index.html
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'Frontend/pages/index.html'));
});

// Start server
app.listen(8080, () => {
  console.log('Server running at http://localhost:8080');
});
