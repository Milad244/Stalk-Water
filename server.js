const express = require('express');
const { execFile } = require('child_process');
const path = require('path');

const app = express();

// Built-in body parsers
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Serve static folders
app.use('/pages', express.static(path.join(__dirname, 'Frontend/pages')));
app.use('/styles', express.static(path.join(__dirname, 'Frontend/styles')));
app.use('/assets', express.static(path.join(__dirname, 'Frontend/assets')));

// Serve index.html at root
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'Frontend/pages/index.html'));
});

// POST to C++ backend
app.post('/users', (req, res) => {
  const { name, weight, gender } = req.body;
  const cppPath = path.join(__dirname, 'Backend/output', process.platform === 'win32' ? 'user.exe' : 'user');

  execFile(cppPath, [name, weight, gender], (error, stdout, stderr) => {
    if (error) {
      console.error('C++ execution error:', error);
      console.error('stderr:', stderr);

      return res.status(500).json({
        error: 'Error running C++ program',
        details: stderr || error.message
      });
    }

    try {
      const data = JSON.parse(stdout);
      res.json(data);
    } catch (err) {
      console.error('Invalid C++ output:', stdout);
      res.status(500).json({
        error: 'Invalid backend response',
        raw: stdout
      });
    }
  });
});


// Start server
app.listen(8080, () => {
  console.log('Server running at http://localhost:8080');
});
