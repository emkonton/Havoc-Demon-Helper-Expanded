# Havoc-Demon-Helper-Expanded

Welcome to the **Havoc-Demon-Helper-Expanded** repository!

This project is designed to enhance the [Havoc C2 Framework](https://github.com/havocframework/havoc) by providing comprehensive, well-structured, and multi-language documentation for the Demon agent's commands. It replaces the original, brief help strings with detailed descriptions, exact usage syntax, and practical examples.

## 🌍 Language Documentation / Dil Seçenekleri

Click on the flags below to read the expanded documentation in your preferred language. All files are located in the `helps/` directory.

* [🇬🇧 English Documentation](helps/english_documentation.md)

* [🇹🇷 Türkçe Dokümantasyon](helps/Türkçe_documentation.md)

* [🇩🇪 Deutsche Dokumentation](helps/german_documentation.md)

* [🇷🇺 Руководство на русском](helps/russian_documentation.md)

* [🇦🇿 Azərbaycanca Sənədlər](helps/azerbaijani_documentation.md)

## ⚙️ Expanded Commands Configuration (`Commands.cc`)

The core feature of this repository is the updated `Commands.cc` file. In the original Havoc repository, the in-client help strings are quite minimal. We have rewritten the `DemonCommandList` structure to provide rich text outputs directly inside your C2 interface.

### How to Install

If you want to see these expanded explanations directly in your Havoc Client terminal when you type `help [command]`, follow these steps:

1. Clone or download this repository.
2. Copy the `Commands.cc` file provided in the root directory.
3. Navigate to your original Havoc C2 source code directory.
4. Replace the existing file located at:
   `client/src/Havoc/Demon/Commands.cc`
   *(Note: In some older versions, it might be in `client/Source/Havoc/Demon/Commands.cpp`)*
5. Recompile your Havoc client using the standard build instructions:
   ```bash
   make client-build
   ```
6. Start your client, interact with a Demon, and type `help shell` or `help token` to see the new descriptions!

*Disclaimer: This repository is an independent helper tool and is not officially affiliated with the Havoc Framework developers. Always test changes in a safe, controlled environment.*
