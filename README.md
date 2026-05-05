# STM32 F407 Quadcopter Drone

> Contrôleur de vol haute performance basé sur le microcontrôleur STM32F407

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-STM32F407-green.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32f407.html)
[![Language](https://img.shields.io/badge/language-C-orange.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![FPU](https://img.shields.io/badge/FPU-enabled-brightgreen.svg)](https://www.arm.com/technologies/floating-point)

## Sommaire

- [À propos](#-à-propos)
- [Fonctionnalités](#-fonctionnalités)
- [Architecture matérielle](#-architecture-matérielle)
- [Prérequis](#-prérequis)
- [Installation](#-installation)
- [Structure du projet](#-structure-du-projet)
- [Utilisation](#-utilisation)
- [Configuration](#-configuration)
- [Optimisations FPU](#-optimisations-fpu)
- [Développement](#-développement)
- [Contribution](#-contribution)
- [Licence](#-licence)

## À propos

Système de contrôle de vol avancé exploitant toute la puissance du **STM32F407** (ARM Cortex-M4 168 MHz) avec FPU matérielle. Conçu pour des performances maximales avec calculs en virgule flottante accélérés, idéal pour des algorithmes de contrôle sophistiqués et du traitement de données intensif.

### Pourquoi le STM32F407 ?

| Caractéristique | STM32F407 | Avantage |
|-----------------|-----------|----------|
| **Fréquence** | 168 MHz | +68% vs F411 |
| **RAM** | 192 KB | +50% pour buffers et logs |
| **Flash** | 1 MB | Place pour fonctionnalités avancées |
| **FPU** | Double précision | Calculs PID ultra-rapides |
| **DSP** | Instructions dédiées | Filtrage optimisé |
| **Périphériques** | 3× SPI, 4× I²C | Capteurs multiples simultanés |

### Points clés
- **Performance** : Contrôle à 1 kHz grâce au FPU matériel
- **Précision** : Calculs flottants double précision
- **Extensible** : Mémoire suffisante pour GPS, télémétrie, OSD
- **Robuste** : Watchdog matériel et mécanismes de failsafe multicouches

## Fonctionnalités

### Contrôle de vol (a implémenter)
- **Boucle de contrôle 1 kHz** optimisée FPU
- **PID cascadé** : angle → rate avec anti-windup
- **Filtres** : Notch, Biquad, PT1, Mahony
- **Modes de vol** : Acro, Angle

### Capteurs et fusion de données (a implémenter)
- **IMU haute fréquence** : 8 kHz gyro, moyenné à 1 kHz
- **Filtrage mahony** : fusion multi-capteurs simple mais robuste
- **Magnétomètre** : AK8963 (50 Hz)

### Communication
- **Protocole RC** : UART radio 2.4 GHz simple par module HC-05 avec réarrangement des trames

### Sécurité et diagnostics
- **Failsafe** : RX loss
- **Logs détaillés** : Debug et analyse post-vol (a implémenter)
- **Limites configurables** : Angles, vitesses, (a implémenter)

## Architecture matérielle

### Composants utilisés

| Composant | Modèle | Spécifications | Notes |
|-----------|--------|----------------|-------|
| MCU | STM32F407VGT6 | 168 MHz, FPU, 1MB Flash | Discovery ou custom PCB |
| IMU | MPU9250 | 8 kHz gyro, ±2000°/s | Magnétoçmètre intégré, bon rapport qualité/prix |
| ESC | 4× BLHeli | PWM 490Hz | temporaire |
| Moteurs | 2212 920KV | 8045 props | lift |
| RX | HC_05 | 2.4GHz bluetooth | portée limitée mais faible latence, temporaire |
| Batterie | LiPo 4S 3200mAh | 50-100C | Autonomie 10-15 min |

### Schéma de connexion STM32F407

```raw
STM32F407VGT6
    ├── SPI1 → IMU (MPU9250) + Magnétomètre (AK8963)
    ├── USART1 → RX (HC-05)
    ├── USART2 → Debug
    ├── TIM1 → PWM Moteurs 1-4
    └── USB → DFU Flash
```
## Prérequis

### Logiciels requis
- **VSCode + STM32CubeIDE Extension**
- **STM32CubeMX** pour configuration hardware
- **STM32CubeProgrammer** pour flash sans ST-Link, besion de la CLI STM32CubeProgrammer pour flasher par USB/DFU à l'aide de "flash_DFU.sh"
- **Git** pour versioning

### Toolchain optionnelle
```bash
# Alternative : GCC ARM toolchain
sudo apt install gcc-arm-none-eabi
sudo apt install openocd
```

### Matériel de développement
- **STM32F4 Discovery** (STM32F407VGT6)
- **ST-Link V2** ou V3
- **Analyseur logique** pour debug I²C/SPI (optionnel)
- **Oscilloscope** (recommandé pour debug PWM)

## Installation

### 1. Cloner le repository
```bash
git clone https://github.com/SiCeater/STM32_F407_Quadcopter_Drone.git
cd STM32_F407_Quadcopter_Drone
```

### 2. Configuration CubeMX
```bash
# Ouvrir le fichier .ioc avec STM32CubeMX
# Vérifier la config des clocks (168 MHz)
# Vérifier activation FPU (Hardware, Double precision)
# Régénérer le code si modifié
```

### 3. Ouvrir dans VSCode
```bash
# File → Open folder
# Sélectionner le dossier source_code/
```

### 5. Compilation
```bash
# cliquer sur la petite roue crantée en bas a gauche
# Vérifier taille : Flash < 1024 KB, RAM < 192 KB
```

### 6. Flash du firmware
```bash
# Connecter ST-Link
# Run → Debug (F11) pour debug
# Ou utiliser le script "flash_DFU.sh" (si pas de ST-Link), pour flasher en USB/DFU, enfoncer le bouton "BOOT" avant de brancher le cable USB pour mettre le F411 en mode DFU puis lancer le script
```

### 7. Vérification post-flash
```bash
# Connecter terminal série (460800 bauds, 8N1)
# Vérifier message de boot
```

## Structure du projet

```raw
STM32_F407_Quadcopter_Drone/
│
├── source_code/                    # Code source principal
│   ├── Core/                       # Fichiers HAL et système
│   │   ├── Src/
│   │   └── Inc/
│   │
│   ├── Drivers/                    # Drivers STM32 HAL
│   │   ├── STM32F4xx_HAL_Driver/
│   │   └── CMSIS/
│   │
│   ├── App/                        # Bibliothèques externes et drivers capteurs
│   │   ├── Src/                    
│   │   └── Inc/                    
│   │
│   ├── *.ioc                       # Configuration STM32CubeMX
│   └── STM32F407VGTX_FLASH.ld      # Linker script
│
├── documentation/                  # Documentation technique
│   ├── hardware/
│   │   └── schematics/             # Schémas électriques
│   └── datasheets/                 # Datasheets référence
│
│
├── .gitignore
├── LICENSE
└── README.md
```

#### 3. Configuration ESC et moteurs
```bash
# SANS HÉLICES !
> motor_test 1 1200   # Test moteur 1 à faible régime
> motor_test 2 1200   # Test moteur 2
> motor_test 3 1200   # Test moteur 3
> motor_test 4 1200   # Test moteur 4

# Vérifier directions de rotation selon configuration (quad X)
# Moteur 1 (avant-gauche) : sens horaire
# Moteur 2 (avant-droit)  : sens anti-horaire
# Moteur 3 (arrière-droit): sens horaire
# Moteur 4 (arrière-gauche): sens anti-horaire
```

### Limites de sécurité

```c
#define MAX_THROTTLE         2000    // µs
#define MIN_THROTTLE         1000    // µs
#define IDLE_THROTTLE        1100    // µs (moteurs armés)

#define MAX_ANGLE_INCLINATION 55     // degrés (Angle mode)
#define MAX_RATE_ROLL        1000    // degrés/s
#define MAX_RATE_PITCH       1000    // degrés/s
#define MAX_RATE_YAW         600     // degrés/s

#define BATTERY_CELLS        4       // 4S LiPo
#define BATTERY_WARNING      14.8    // V (3.7V/cellule)
#define BATTERY_CRITICAL     12.8    // V (3.2V/cellule - atterrir!)
```

### Debugging

```c
// Utiliser les fonction de debug decrites dans debug.c

// Analyseur logique sur GPIO pour timing
HAL_GPIO_WritePin(DEBUG_GPIO, GPIO_PIN_0, 1);  // Start marker
rate_controller();
HAL_GPIO_WritePin(DEBUG_GPIO, GPIO_PIN_0, 0);  // End marker
```

## Contribution

Les contributions sont les bienvenues ! 

### Comment contribuer

1. **Fork** le projet
2. Créer une **branche feature** (`git checkout -b feature/NouveauMode`)
3. **Commiter** (`git commit -m 'Add GPS follow mode'`)
4. **Push** (`git push origin feature/NouveauMode`)
5. Ouvrir une **Pull Request**

### Guidelines

- **Code style** : Suivre les conventions existantes (camelCase, indentation 4 espaces)
- **Commentaires** : Français accepté, anglais recommandé pour code partagé
- **Tests** : Ajouter tests unitaires si applicable
- **Documentation** : Mettre à jour README et guides si nécessaire
- **Performance** : Mesurer impact sur temps de boucle (objectif < 800 µs)

### Idées de contributions

- [ ] Régler le probleme de vitesse des USART/UART
- [ ] Finir de developper le driver MPU9250
- [ ] Implémenter les filtres gyro (peut etre y en a t'ils des suffisnat déjà intégrés au MPU9250 ?)
- [ ] Implementer la boucle de controle
- [ ] Fusion des données IMU par filtre mahony ou un kalman 
- [ ] Implémenter les PID attiude

## Licence

Ce projet est sous licence **MIT**

## Ressources

### Tuning et théorie
- [PID Tuning Guide](https://oscarliang.com/quadcopter-pid-explained-tuning/)
- [Filters Explained](https://www.rcgroups.com/forums/showthread.php?2923077)

## Contact

**SiCeater** - [@SiCeater](https://github.com/SiCeater)

**Lien du projet** : [https://github.com/SiCeater/STM32_F407_Quadcopter_Drone](https://github.com/SiCeater/STM32_F407_Quadcopter_Drone)

---

**Si ce projet vous aide, donnez-lui une étoile !**
