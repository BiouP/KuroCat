<div align="center">

# 🐱 KuroCat

**Un chat de bureau léger qui réagit au clavier et à la souris · macOS, Windows, Linux et UOS**

[简体中文](README.md) | [English](README.en.md) | **Français**

[Site officiel et démo](https://kurocat.cc/en/) · [Atelier de pelages](https://workshop.kurocat.cc/) · [Guide OBS](https://kurocat.cc/obs-guide/)

<img src="assets/demo_typing.gif" width="265" alt="Le chat tape au clavier"/>
<img src="assets/demo_hunting.gif" width="265" alt="Le chat suit la souris en mode chasse"/>
<img src="assets/demo_combo.gif" width="265" alt="Le chat utilise la souris et tape avec sa patte arrière"/>

</div>

## Ce que fait KuroCat

- **Clavier et souris**. Le chat réagit aux touches maintenues et aux combinaisons, y compris dans les jeux compatibles. Il peut utiliser sa patte arrière pour la troisième touche et sa queue pour la quatrième. Le compteur affiche les frappes du jour et les frappes par minute.
- **Animation 2,5D**. Le chat tourne la tête vers le pointeur. Si vous agitez la souris, il s’accroupit et dilate ses pupilles. Caressez-le pour le faire ronronner ou laissez-le s’endormir.
- **Personnalisation**. Changez le pelage, le thème du clavier, la couleur des yeux, la taille et l’orientation. Vous pouvez aussi importer des pelages `.kurocat` et des thèmes de clavier `.kurokb`.
- **Superposition OBS**. Choisissez la capture sur fond transparent ou sur fond vert. Le réglage de passage des clics permet d’utiliser les fenêtres derrière le chat.
- **Traitement local**. L’application utilise les entrées clavier et souris en mémoire pour animer le chat. Elle conserve les compteurs agrégés de l’activité.

## Activer le français

Le français est sélectionné au premier lancement si le système est en français et qu’aucune langue n’est enregistrée dans KuroCat. Pour le choisir manuellement, faites un clic droit sur le chat ou ouvrez le menu de l’icône KuroCat, puis choisissez **Réglages → Langue → Français**. Depuis l’interface anglaise, cherchez **Settings → Language**. Depuis l’interface chinoise, cherchez **设置 → 界面语言** (**语言 / Language** sur macOS).

## Installer ou compiler

Les binaires de la version d’origine sont disponibles sur [GitHub Releases](https://github.com/chanke17/KuroCat/releases/latest). Pour utiliser la traduction de ce fork, compilez le code de ce dépôt avec les commandes ci-dessous.

### macOS 11 ou ultérieur

Le script produit une application universelle pour Apple Silicon et Intel. Au premier lancement, activez KuroCat dans **Réglages Système → Confidentialité et sécurité → Surveillance de l’entrée**, puis relancez l’application depuis son menu. Maintenez **⌥ Option** pour déplacer le chat lorsque le passage des clics est activé.

```bash
./build.sh
open KuroCat.app
```

### Windows x64

Exécutez `build.bat` depuis l’invite de commandes pour développeurs Visual Studio. Le script produit `KuroCat.exe` dans le dossier `windows`. Le menu est accessible depuis l’icône de notification. Quand le passage des clics est activé, maintenez **Alt** et faites un clic droit sur le chat, ou utilisez **Ctrl + Alt + Maj + P**.

```bat
cd windows
build.bat
```

### Linux, UOS et Kylin

Sous Debian, Ubuntu ou une distribution dérivée, installez les bibliothèques de développement puis compilez. KuroCat utilise XInput2 sous X11 et peut utiliser `evdev` pour capter les entrées globales sous Wayland lorsque l’utilisateur dispose des droits nécessaires.

```bash
sudo apt install g++ pkg-config libgtk-3-dev libcairo2-dev libx11-dev libxi-dev
cd linux
./build.sh
./kurocat
```

Vous pouvez aussi créer un paquet `.deb` avec `./build_deb.sh`. Pour les autres modes d’installation, consultez le [README du projet en anglais](README.en.md).

## Pelages et ressources

| Ressource | Contenu |
| --- | --- |
| [Atelier de pelages](https://workshop.kurocat.cc/) | Créer et télécharger des pelages et des thèmes de clavier |
| [Guide OBS](https://kurocat.cc/obs-guide/) | Configurer la capture avec le fond transparent ou le fond vert `#00FF00` |
| [Format des pelages](docs/skin-format.md) | Structure des fichiers `.kurocat` et schéma des coordonnées |
| [Serveur MCP](mcp/README.md) | Créer et installer des pelages via un client MCP |

KuroCat est distribué sous [licence MIT](LICENSE).
