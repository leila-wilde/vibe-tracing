<a id="fr">

<div align=center>
    <a href="#en">EN</a> . 
    <a href="#fr">FR</a>

# Vibe Tracing

*Le **projet de jour 3** du défi MiniVibes - Un ray tracer en C créé en une journée.*
---
</div>

## Aperçu

**Vibe Tracing** est le défi de jour 3 du MiniVibes. L'objectif: créer un programme de **ray tracing complet en C** en une seule journée via collaboration avec des agents IA (vibe coding).

Ce défi démontre comment collaborer efficacement avec les agents de codage IA pour construire une application graphique 3D ambitieuse sous des contraintes strictes de temps. Le ray tracing est un classique de l'infographie qui produit une sortie visuelle en haute qualité, ce qui en fait un excellent test du workflow IA en mode "vibe".

## Qu'est-ce que le vibe coding?

Le vibe coding désigne la compétence émergente de travailler efficacement avec des agents de codage IA. À mesure que les agents IA deviennent plus capables, savoir comment les inviter, les guider et collaborer avec eux devient aussi important que les compétences de codage traditionnelles.

## Contraintes du projet

Le défi MiniVibes fonctionne sous des contraintes strictes:
- **temps limité**: un jour par projet
- **jetons limités**: utilisation de modèles "mini" (multiplicateur 0,33x) la plupart du temps
- **budget limité**: une demande premium par projet/jour

Malgré ces limitations, l'idée est de créer des projets riches en fonctionnalités et de qualité production qui démontrent les compétences en ingénierie de prompts et en communication avec les agents.

## Exigences clés

- spécifications complètes du projet avant le développement
- contrôle de version basé sur git avec commits intelligents
- prompting transparent (tous les prompts documentés dans `COPILOT.md`)
- code initial généré entièrement par les agents IA
- soumission `SESSION.md` en fin de journée

## Structure du projet

```
vibe-tracing/
├── README.md              # Ce fichier
├── Specification.md       # Spécification technique du projet
├── LICENSE                # Licence du projet
├── COPILOT.md             # Instructions pour l'agent
├── SESSION.md             # Journal de session
├── docs/
│   ├── MiniVibesConsigne.md
│   └── minivibes.png
├── src/
│   ├── main.c             # Point d'entrée et boucle de rendu
│   ├── vec3.h/c           # Utilitaires de mathématiques vectorielles
│   ├── ray.h              # Définition du rayon
│   ├── camera.h/c         # Logique de caméra et viewport
│   ├── material.h/c       # Logique de diffusion (scatter)
│   ├── hittable.h         # Interface abstraite pour les objets
│   ├── sphere.h/c         # Implémentation de la sphère
│   └── utils.h            # Constantes et utilitaires aléatoires
├── tests/                 # Tests unitaires
│   └── test_vec3.c
├── output/                # Images rendues (.ppm)
└── Makefile               # Système de compilation
```

## Compétences

Ce projet démontre:
- **compétences de collaboration IA** - de plus en plus appréciées dans les entretiens techniques et les rôles
- **développement rapide** - construire des fonctionnalités complètes sous contraintes
- **pratiques de codage propre** - workflow Git approprié et organisation du code
- **ingénierie de prompts** - une compétence technique pratique et émergente
- **gestion du temps** - livrer un travail de qualité dans des délais stricts

## Références sur le Ray Tracing

Les concepts logiques et les algorithmes de ce projet sont basés sur les fondamentaux fournis par la série de livres "Ray Tracing in One Weekend".

**Auteurs**: Peter Shirley, Trevor David Black, Steve Hollasch.

**Titre de la série**: Ray Tracing in One Weekend Series (v4.0.2).

**URL:** https://raytracing.github.io/

---

<a id="en">

<div align=center>
    <a href="#en">EN</a> . 
    <a href="#fr">FR</a>

# Vibe Tracing

*The **day 3 project** of the MiniVibes challenge - A ray tracer in C built in one day.*
---
</div>

## Overview

**Vibe Tracing** is the day 3 challenge of MiniVibes. Goal: create a **complete ray tracing program in C** in a single day through AI agent collaboration (vibe coding).

This challenge showcases how to collaborate effectively with AI coding agents to build an ambitious 3D graphics application under strict time constraints. Ray tracing is a classic in computer graphics that produces high-quality visual output, making it an excellent test of the AI agent workflow in "vibe" mode.

## What is vibe coding?

Vibe coding refers to the emerging skill of effectively working with AI coding agents. As AI agents become more capable, knowing how to prompt, guide, and collaborate with them is becoming as important as traditional coding skills.

## Project constraints

The MiniVibes challenge operates under strict constraints:
- **limited time**: one day per project
- **limited tokens**: using "mini" models (0.33x multiplier) most of the time  
- **limited budget**: one premium request per project/day

Despite these limitations, the idea is to create feature-rich, production-quality projects that demonstrate prompt engineering and agent communication skills. 

## Key requirements

- complete project specifications before development
- git-based version control with intelligent commits
- transparent prompting (all prompts documented in `COPILOT.md`)
- initial code generated entirely by AI agents
- `SESSION.md` prompt record

## Project structure

```
vibe-tracing/
├── README.md              # This file
├── Specification.md       # Technical project specification
├── LICENSE                # Project license
├── COPILOT.md             # Agent instructions
├── SESSION.md             # Session log
├── docs/
│   ├── MiniVibesConsigne.md
│   └── minivibes.png
├── src/
│   ├── main.c             # Entry point and render loop
│   ├── vec3.h/c           # Vector math utilities
│   ├── ray.h              # Ray definition
│   ├── camera.h/c         # Camera and viewport logic
│   ├── material.h/c       # Scatter logic
│   ├── hittable.h         # Abstract interface for objects
│   ├── sphere.h/c         # Sphere implementation
│   └── utils.h            # Constants and random helpers
├── tests/                 # Unit tests
│   └── test_vec3.c
├── output/                # Rendered images (.ppm)
└── Makefile               # Build system
```

## Skills

This project demonstrates:
- **AI collaboration skills** - increasingly valued in tech interviews and roles
- **rapid development** - building complete features under constraints
- **clean coding practices** - proper Git workflow and code organization
- **prompt engineering** - a practical, emerging technical skill
- **time management** - delivering quality work within strict timeframes

For complete details, see complete project brief (French & English) [MiniVibesConsigne.md](./docs/MiniVibesConsigne.md)

## Ray Tracing references

The specification logic and algorithms in this project were based on the foundational concepts provided in the "Ray Tracing in One Weekend" book series.

**Authors**: Peter Shirley, Trevor David Black, Steve Hollasch.

**Series Title**: Ray Tracing in One Weekend Series (v4.0.2).

**URL:** https://raytracing.github.io/

---

