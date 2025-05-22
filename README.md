# 🐚 Minishell

## 🎯 Objectif

Ce projet, réalisé dans le cadre du cursus de l'école 42, consiste à développer un interpréteur de commandes minimaliste en langage C, reproduisant certaines fonctionnalités essentielles de Bash. L'objectif est de comprendre les mécanismes internes d'un shell Unix, tels que la gestion des processus, les redirections, les pipes et les variables d'environnement.

## ⚙️ Fonctionnalités implémentées

- **Affichage du prompt** : Affiche un prompt interactif attendant les commandes de l'utilisateur.
- **Exécution de commandes** :
  - Commandes avec chemin absolu ou relatif (ex. `/bin/ls`, `./a.out`).
  - Commandes disponibles dans le `PATH` (ex. `ls`, `grep`).
- **Redirections** :
  - `>` : redirection de la sortie standard.
  - `>>` : redirection en mode ajout.
  - `<` : redirection de l'entrée standard.
  - `<<` : here-document.
- **Pipes** : Gestion des pipes (`|`) pour chaîner plusieurs commandes.
- **Variables d'environnement** :
  - Expansion des variables (ex. `$HOME`, `$?`).
  - Gestion des variables via les built-ins `export`, `unset`, `env`.
- **Gestion des signaux** :
  - `Ctrl+C` : interruption de la commande en cours.
  - `Ctrl+D` : fermeture du shell.
  - `Ctrl+\` : ignoré.
- **Built-ins implémentés** :
  - `echo` (avec option `-n`)
  - `cd` (avec chemins relatifs ou absolus)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
