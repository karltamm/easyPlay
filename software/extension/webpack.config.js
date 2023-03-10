const path = require("path");

const tsDirPath = path.join(__dirname, "src", "typescript");
const outputDirPath = path.join(__dirname, "dist");

module.exports = {
  mode: "development",
  devtool: false,
  entry: {
    background: path.join(tsDirPath, "backgroundScripts", "background.ts"),
    content: path.join(tsDirPath, "contentScripts", "content.ts"),
  },
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        use: "ts-loader",
        exclude: /node_modules/,
      },
      {
        test: /\.s[ac]ss$/i,
        use: ["style-loader", "css-loader", "sass-loader"],
      },
      {
        test: /\.png/,
        type: "asset/inline",
      },
    ],
  },
  resolve: {
    extensions: [".tsx", ".ts", ".js"],
  },
  output: {
    path: outputDirPath,
    filename: "[name].js",
  },
};
