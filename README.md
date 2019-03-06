# riro

This project is a copy of https://github.com/lfaucon/robot implemented with ReasonReact.

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up `build/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

You should also copy (or create a symbolic link) `src/style.css` to `build/style.css`.

## Build for Production

```sh
npm run build
npm run webpack:production
```
