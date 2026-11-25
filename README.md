<div align="center">

# 🐱 KuroCat

**Un chat de bureau léger et libre qui réagit au clavier et à la souris · macOS, Windows, Linux et UOS**

<p>
  <a href="https://github.com/chanke17/KuroCat/releases/latest"><img src="https://img.shields.io/github/v/release/chanke17/KuroCat?style=flat-square&amp;color=1f6feb&amp;label=Version%20d%27origine" alt="Dernière version du projet d’origine"/></a>
  <a href="https://github.com/chanke17/KuroCat/releases"><img src="https://img.shields.io/github/downloads/chanke17/KuroCat/total?style=flat-square&amp;color=2ea44f&amp;label=T%C3%A9l%C3%A9chargements" alt="Téléchargements du projet d’origine"/></a>
  <a href="https://github.com/chanke17/KuroCat/stargazers"><img src="https://img.shields.io/github/stars/chanke17/KuroCat?style=flat-square&amp;color=e3b341&amp;label=%C3%89toiles" alt="Étoiles du projet d’origine sur GitHub"/></a>
  <a href="LICENSE"><img src="https://img.shields.io/github/license/chanke17/KuroCat?style=flat-square&amp;color=8957e5&amp;label=Licence" alt="Licence MIT"/></a>
</p>

<p>
  <b>Français</b> | <a href="README.en.md">English</a> | <a href="README.zh.md">简体中文</a>
</p>

<p>
  <a href="https://kurocat.cc/en/">🌐 Site officiel et démo</a> ·
  <a href="https://workshop.kurocat.cc/">🎨 Atelier de pelages</a> ·
  <a href="https://kurocat.cc/obs-guide/">🎥 Guide OBS</a> ·
  <a href="https://github.com/chanke17/KuroCat/releases/latest">⬇️ Versions du projet d’origine</a>
</p>

<p>
  <img src="assets/demo_typing.gif" width="265" alt="Le chat tape au clavier"/>
  <img src="assets/demo_hunting.gif" width="265" alt="Le chat suit la souris en mode chasse"/>
  <img src="assets/demo_combo.gif" width="265" alt="Le chat utilise la souris et tape avec sa patte arrière"/>
</p>

<sub>macOS (Swift, CoreGraphics et IOHIDManager) · Windows (C++17, GDI+ et Raw Input) · Linux et UOS (C++17, GTK3, Cairo, XInput2 et evdev)</sub>

</div>

---

## Ce que fait KuroCat

- **Clavier et souris.** Le chat réagit aux touches maintenues, aux combinaisons et aux mouvements de souris. L’animation peut utiliser une patte arrière dès la troisième touche et la queue à partir de la quatrième. Un compteur affiche les frappes du jour et les frappes par minute.
- **Animation 2,5D.** La tête, les oreilles, les yeux et les moustaches suivent le pointeur en perspective. Si vous agitez la souris, le chat s’accroupit, dilate ses pupilles et remue la queue plus vite.
- **Caresses et sommeil.** Caressez la tête du chat pour le voir fermer les yeux et ronronner. Il s’endort au bout d’un moment sans interaction.
- **Apparence personnalisable.** Changez le pelage, la couleur des yeux, la taille et l’orientation. Choisissez parmi trois thèmes de clavier, importez des pelages `.kurocat` et des thèmes de clavier `.kurokb`, ou activez le défilement lumineux du clavier, qui accélère avec le nombre de touches enfoncées.
- **Superposition OBS.** Choisissez une fenêtre transparente ou un fond vert `#00FF00`. Le mode de passage des clics permet d’utiliser les fenêtres derrière le chat. KuroCat peut aussi se lancer à l’ouverture de session.
- **Application native.** Le projet d’origine annonce un exécutable Windows d’environ 802 Ko, sans dépendance d’exécution externe. Le rendu baisse automatiquement à 30, 20 ou 10 images par seconde selon l’activité pour limiter la consommation de ressources.

<details>
<summary>🎮 Capture clavier et souris selon le système</summary>

- **macOS** utilise `IOHIDManager` et `CGEventTap`. Il prend en charge les touches maintenues, les combinaisons, les touches de modification (`⌘`, `⇧`, `⌥`, `⌃`, `Fn`), les flèches et les touches `F1` à `F12`.
- **Windows** utilise `Raw Input` (`RIDEV_INPUTSINK`) pour capter les codes matériels du clavier et les petits mouvements de souris, y compris dans les jeux DirectX et Vulkan compatibles.
- **Linux, UOS et Kylin** utilisent `XInput2` sous X11 et `evdev` lorsque l’utilisateur a accès aux périphériques d’entrée. Sous X11, la capture fonctionne sans `sudo` sur UOS, Deepin et Ubuntu.

</details>

<details>
<summary>🖼️ Aperçu des pelages intégrés</summary>

| Chat noir classique | Chat siamois |
| :---: | :---: |
| <img src="assets/preview_black.jpg" width="420" alt="Aperçu du chat noir classique"/> | <img src="assets/preview_siamese.jpg" width="420" alt="Aperçu du chat siamois"/> |

| Américain à poil court tigré argenté et blanc | Chat roux et blanc |
| :---: | :---: |
| <img src="assets/preview_shorthair.jpg" width="420" alt="Aperçu du chat tigré argenté"/> | <img src="assets/preview_orangeWhite.jpg" width="420" alt="Aperçu du chat roux et blanc"/> |

<p align="center">
  <img src="assets/preview_tabby_windows.png" width="520" alt="Chat noir classique et chat tigré brun, assis et en train de taper"/>
</p>

</details>

---

## Activer le français

Au premier lancement, ce fork sélectionne le français si le système est en français et qu’aucune langue n’est enregistrée. Vous pouvez aussi ouvrir le menu du chat ou de l’icône KuroCat, puis choisir **Réglages → Langue → Français**.

Depuis l’interface anglaise, cherchez **Settings → Language**. Depuis l’interface chinoise, cherchez **设置 → 界面语言**, ou **设置 → 语言 / Language** sur macOS.

## Installer ou compiler

Les exécutables du projet d’origine sont disponibles sur [GitHub Releases](https://github.com/chanke17/KuroCat/releases/latest). Pour utiliser l’interface française de ce fork, compilez les sources de ce dépôt avec les commandes ci-dessous.

### 🍎 macOS 11 ou ultérieur · Apple Silicon et Intel

Pour installer la version d’origine, décompressez `KuroCat-macOS-universal.zip`, puis glissez `KuroCat.app` dans **Applications**. L’icône KuroCat apparaît dans la barre des menus.

Au premier lancement, autorisez KuroCat dans **Réglages Système → Confidentialité et sécurité → Surveillance de l’entrée**, puis relancez l’application depuis son menu. Lorsque le passage des clics est activé, maintenez **⌥ Option** pour déplacer le chat ou ouvrir son menu contextuel.

<details>
<summary>Compiler pour macOS</summary>

```bash
chmod +x build.sh
./build.sh
open KuroCat.app
```

Le script produit une application universelle pour Apple Silicon et Intel.

</details>

### 🪟 Windows x64 · 7 SP1, 8, 10 et 11

La version d’origine se lance en ouvrant `KuroCat-Windows-x64.exe`. Vous pouvez accéder au menu depuis l’icône de notification.

Lorsque le passage des clics est activé, utilisez **Ctrl + Alt + Maj + P** pour le désactiver, ou maintenez **Alt** pour déplacer le chat ou faire un clic droit. Vous pouvez aussi rouvrir l’exécutable pour retrouver le menu.

<details>
<summary>Compiler pour Windows et résoudre les problèmes courants</summary>

- Si le chat suit la souris mais ignore le clavier d’un jeu exécuté en administrateur, ouvrez le menu de KuroCat et choisissez **Relancer en administrateur**.
- Si le chat disparaît en plein écran exclusif, utilisez le mode fenêtre sans bordure du jeu.
- Si une mise à jour est toujours proposée après un téléchargement, vérifiez quelle version est en cours d’exécution.

Depuis l’invite de commandes pour développeurs Visual Studio, lancez la compilation avec MSVC.

```bat
cd windows
build.bat
```

Vous pouvez également utiliser CMake depuis le dossier `windows`.

```bat
cmake -B build && cmake --build build --config Release
```

</details>

### 🐧 Linux, UOS et Kylin · x86-64 et ARM64

Le projet prend en charge notamment Ubuntu 20.04+, Debian 11+, Deepin, UOS, Kylin, Arch et Fedora.

- **Installation sans privilèges administrateur.** Décompressez l’archive `KuroCat-Linux-x86_64.tar.gz` ou `KuroCat-Linux-arm64.tar.gz`, puis lancez `bash install.sh`. Les fichiers sont installés dans `~/.local`. Pour les retirer, lancez `bash uninstall.sh`.
- **Paquet Debian.** Installez le paquet correspondant à votre architecture. Sur x86-64, utilisez `sudo apt install ./KuroCat-Linux-amd64.deb`.
- **Wayland.** La capture globale nécessite l’accès aux périphériques `evdev`. Si l’accès est accordé via le groupe `input` sur votre distribution, ouvrez une nouvelle session après y avoir été ajouté.

<details>
<summary>Compiler pour Linux</summary>

Sur Debian, Ubuntu et leurs dérivées, installez les dépendances de développement, puis compilez l’application.

```bash
sudo apt install g++ pkg-config libgtk-3-dev libcairo2-dev libx11-dev libxi-dev
cd linux
chmod +x build.sh build_deb.sh
./build.sh
./kurocat
```

Pour créer un paquet Debian après la compilation, exécutez `./build_deb.sh`. Sur les machines modestes, la fréquence d’image adaptative réduit la charge en évitant de forcer le mode 60 i/s.

</details>

---

## Ressources

| Ressource | Contenu |
| --- | --- |
| [Site officiel et démo 2,5D](https://kurocat.cc/en/) | Essayer le chat dans le navigateur et retrouver les téléchargements avec leurs sommes SHA-256 |
| [Atelier de pelages](https://workshop.kurocat.cc/) | Créer un pelage, prélever des couleurs sur une image et télécharger les créations de la communauté |
| [Guide OBS](https://kurocat.cc/obs-guide/) | Configurer la capture transparente et le fond vert pour le streaming |
| [Serveur MCP KuroCat](mcp/README.md) | Créer et installer des pelages depuis un client MCP avec le serveur Node.js du projet |
| [Spécification du format de pelage](docs/skin-format.md) | Consulter les champs du format `.kurocat` et le schéma des coordonnées |

## Contribuer

- Partagez vos pelages et thèmes de clavier en proposant une contribution au [dépôt de l’atelier KuroCat](https://github.com/chanke17/KuroCat-Workshop).
- Pour l’application d’origine, signalez un problème ou proposez une contribution dans le [dépôt KuroCat](https://github.com/chanke17/KuroCat).

<details>
<summary>Arborescence du projet</summary>

```text
KuroCat/
├── Sources/                    # Sources Swift pour macOS
├── Resources/                  # Métadonnées et icône macOS
├── build.sh                    # Compilation universelle pour macOS
├── windows/                    # Application Windows en C++17
├── linux/                      # Application Linux et UOS en C++17
├── mcp/                        # Serveur MCP en Node.js
├── docs/                       # Format des pelages et captures d’écran
└── .github/workflows/build.yml # Compilation et publication multiplateformes
```

</details>

## Confidentialité et signature du code

KuroCat traite les signaux du clavier et de la souris en mémoire pour animer le chat et calculer les statistiques. Le contenu des frappes n’est pas enregistré. L’application conserve les compteurs agrégés et contacte le serveur de mises à jour pour rechercher de nouvelles versions.

Le projet d’origine utilise la signature de code fournie par [SignPath.io](https://signpath.io/) et le certificat de la [SignPath Foundation](https://signpath.org/). Les mainteneurs du dépôt d’origine révisent les changements et le propriétaire, `chanke17`, approuve la signature des versions.

## Évolution des étoiles du projet d’origine

<a href="https://star-history.com/#chanke17/KuroCat&amp;Date">
 <picture>
   <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=chanke17/KuroCat&amp;type=Date&amp;theme=dark" />
   <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=chanke17/KuroCat&amp;type=Date" />
   <img alt="Évolution du nombre d’étoiles du projet d’origine" src="https://api.star-history.com/svg?repos=chanke17/KuroCat&amp;type=Date" width="600" />
 </picture>
</a>

## Licence

KuroCat est distribué sous [licence MIT](LICENSE).
