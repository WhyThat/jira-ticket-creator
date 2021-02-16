const path = require('path');
const { CleanWebpackPlugin } = require('clean-webpack-plugin');

module.exports = {
  entry: {
    home: path.resolve(__dirname, '../src/content_scripts/home_script.js')
  },
  plugins: [
    new CleanWebpackPlugin(),
  ],
  output: {
    path: path.resolve(__dirname, '../build'),
    filename: '[name].js'
  }
};
