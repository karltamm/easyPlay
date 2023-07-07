const fs = require("fs");

const filePath = process.argv[2];
const tempFile = "./temp.txt";
const regex = /^.*\.innerHTML\s*=.*/;

fs.writeFileSync(tempFile, "");

const fileContents = fs.readFileSync(filePath, "utf8");
const filteredContents = fileContents
  .split("\n")
  .filter((line) => !regex.test(line))
  .join("\n");

fs.writeFileSync(tempFile, filteredContents);

fs.unlinkSync(filePath);
fs.renameSync(tempFile, filePath);
