module.exports = {
    entry: './app/wiki.js', 
    output: {
        filename: '[name].bundle.js', 
        path: __dirname, 
        publicPath: __dirname
    }
};
