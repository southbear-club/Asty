## Your Project Name

The project description here.

## Development Cli Command

[ovine cli doc](https://ovine.igroupes.com/org/docs/advance/cli)

```bash
# there are examples of 'yarn', you also can use 'npm'.
yarn start # start dev server
yarn build # build bundle files
yarn ovine help # more ovine cli information

# optional command
yarn scss # build scss files
yarn dll # build webpack dll files
```

## Projects Are Mainly Dependent On

- [ovine](https://github.com/CareyToboo/ovine) the main core lib.
- [amis](https://baidu.github.io/amis/docs/start/getting-started) extend the amis lib.
- [styled-components](https://styled-components.com) css styles in js.
- [font-awesome](http://fontawesome.dashgame.com) all icons out of box.
- [bootstrap](https://getbootstrap.com/docs/4.4/getting-started/introduction) full bootstrap features.
- `rust`用于构建`PC`应用程序
- [tauri](https://github.com/tauri-apps/tauri)复用前端，直接转换为`PC`应用程序

## Vscode Plugins You May Need

- `eslint` - es code linter
- `prettier` - prettify your codes
- `vscode styled component`- css in js styles highlight
- `search node_modules` - search file from `node_modules`
- `code spell checker` - for words spell check

> Any Issues? [Let Me Know](https://github.com/CareyToboo/ovine/issues).

## 项目创建步骤

1. 创建前端项目，参考[ovine](https://ovine.igroupes.com/org/docs/guides/start)快速开始；

```shell
npx @ovine/init@latest init dmp-ui
cd dmp-ui
yarn install
yarn start
```

2. 添加`tauri`，参考[tauri](https://tauri.studio/en/docs/usage/development/integration)；

安装 rust/nodejs 相关：

```shell
# linux安装，windows去看官网
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env

# 如果你不是在Ubuntu下开发PC软件，则跳过这一步
sudo apt update && sudo apt install libwebkit2gtk-4.0-dev \
  build-essential \
  curl \
  wget \
  libssl-dev \
  appmenu-gtk3-module \
  libgtk-3-dev \
  squashfs-tools

# windows去官网下载
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.2/install.sh | bash

nvm install node --latest-npm
nvm use node

cargo install tauri-bundler --force
```

```shell
yarn add tauri
```

3. `package.json`中添加：

```json
"scripts": {
  "tauri": "tauri"
}
```

4. 修改`package.json`中的：

```json
"start": "ovine dev --mock", -->> "start": "ovine dev --mock -p 9876",
// 这个端口需要和你配置的tauri端口一致，因为tauri应用也是客户端，需要请求服务器，调试时来启动这个模拟服务器端口
```

5. 初始化`tauri`:

```shell
yarn tauri init
```

6. 启动：

```shell
yarn start
yarn tauri dev
# 你也可以在配置里将两个命令合成一个
```

7. 构建发布：

```shell
yarn build
yarn tauri build
```
