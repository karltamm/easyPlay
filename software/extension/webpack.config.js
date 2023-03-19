const path = require("path");

const DIRS = {
  typescript: path.join(__dirname, "src", "typescript"),
  siteHandlers: path.join(__dirname, "src", "typescript", "contentScripts", "siteHandlers"),
  output: path.join(__dirname, "dist"),
};

module.exports = {
  mode: "development",
  devtool: false,
  entry: {
    background: path.join(DIRS.typescript, "backgroundScripts", "background.ts"),
    youtubeHandler: path.join(DIRS.siteHandlers, "youtubeHandler.ts"),
    courseraHandler: path.join(DIRS.siteHandlers, "courseraHandler.ts"),
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
    path: DIRS.output,
    filename: "[name].js",
  },
  experiments: {
    topLevelAwait: true,
  },
};
