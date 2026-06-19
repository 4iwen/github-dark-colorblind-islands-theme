# GitHub Dark Colorblind Islands Theme

<!-- Plugin description -->
GitHub Light and Dark Colorblind inspired themes adapted for JetBrains IDEs with the Islands parent themes.

The UI palettes follow GitHub's colorblind / Primer tokens, with blue success/accent states,
orange danger/severe states, and GitHub-style syntax colors for comments, strings, constants,
functions, variables, and entities.

This theme specifically supports the new "Islands" UI elements and includes italic and no-italic
variants for both dark and light modes.
<!-- Plugin description end -->

## Install

Build the plugin ZIP and install it from disk in CLion:

```sh
./gradlew clean buildPlugin
```

Then open **Settings | Plugins | Install Plugin from Disk...** and select:

```text
build/distributions/GitHub Dark Colorblind Islands-0.2.1.zip
```

## Variants

- `GitHub Dark Colorblind Islands`: italic comments and bold-italic keywords.
- `GitHub Dark Colorblind Islands No Italic`: upright comments and bold-only keywords.
- `GitHub Light Colorblind Islands`: light mode with italic comments and bold-italic keywords.
- `GitHub Light Colorblind Islands No Italic`: light mode with upright comments and bold-only keywords.

## Showcase

![GitHub Dark Colorblind Islands editor syntax showcase](docs/showcase/editor-syntax.png)

![GitHub Dark Colorblind Islands stream and control-flow showcase](docs/showcase/editor-streams.png)

## Development

The plugin identity is configured as `dev.aiwen.github-dark-colorblind-islands-theme`.

Open `examples/theme_showcase.cpp` in CLion to inspect the editor colors across C++ comments,
keywords, strings, constants, functions, classes, templates, diagnostics, and control flow.

## Attribution

Forked from the MIT-licensed Gruvbox Islands theme project. The icon is intentionally abstract
and only uses this theme palette; it does not copy GitHub product marks.
