var path = require('path');

module.exports = {
    entry: './app/wiki.js', 
    output: {
        filename: 'wiki.bundle.js', 
        path: path.join(__dirname, 'public/'), 
        publicPath: __dirname,
    }
};
