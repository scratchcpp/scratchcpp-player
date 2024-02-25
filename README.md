<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <!-- TODO: Add logo: <a href="https://github.com/scratchcpp/scratchcpp-player">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->

<h3 align="center">ScratchCPP Player</h3>

  <p align="center">
    ScratchCPP is an application which runs Scratch projects, written in C++ and QML.
    It uses the <a href="https://github.com/scratchcpp/scratchcpp-render">scratchcpp-render</a> library for rendering,
    which uses <a href="https://github.com/scratchcpp/libscratchcpp">libscratchcpp</a> to parse and run Scratch projects.
    <br />
    <!-- TODO: Add link to documentation: <a href="https://github.com/scratchcpp/scratchcpp-player"><strong>Explore the docs »</strong></a>
    <br /> -->
    <br />
    <a href="https://github.com/scratchcpp/scratchcpp-player/issues">Report Bug</a>
    ·
    <a href="https://github.com/scratchcpp/scratchcpp-player/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![ScratchCPP screenshot][product-screenshot]](https://github.com/scratchcpp/scratchcpp-player)

**ScratchCPP** is an ongoing project to build a fast and lightweight Scratch project player.
It might not be as fast as TurboWarp (yet), but the main goal is to develop a project player
that is **lightweight**.

Scratch requires a web browser to run and web browsers typically require a lot of resources (memory).
The ScratchCPP project player doesn't depend on a web browsers and uses less memory.

## NOTE
This application is still in development and it doesn't run most Scratch projects correctly.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

We're working on the documentation, it'll be available soon.
<!-- TODO: Add link to documentation -->

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage
The UI is very simple to use. Paste the project URL in the text box and press the `Load` button.
When the project loads, click on the green flag button to run it.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] Loading from URL
- [x] Loading from a local file
- [x] Green flag button
- [x] Stop button
- [ ] Turbo mode
- [ ] FPS options
- [ ] Stage size options
- [ ] HQ pen
- [ ] Mute sounds
- [ ] Theme options (light/dark mode, accent color, etc.)

See the [open issues](https://github.com/scratchcpp/scratchcpp-player/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Format changed source files (`clang-format src/some_file.cpp`)
4. Commit your Changes (`git add -A && git commit -m 'Add some AmazingFeature'`)
5. Push to the Branch (`git push origin feature/AmazingFeature`)
6. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the GNU General Public License. See [LICENSE](LICENSE) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/scratchcpp/scratchcpp-player.svg?style=for-the-badge
[contributors-url]: https://github.com/scratchcpp/scratchcpp-player/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/scratchcpp/scratchcpp-player.svg?style=for-the-badge
[forks-url]: https://github.com/scratchcpp/scratchcpp-player/network/members
[stars-shield]: https://img.shields.io/github/stars/scratchcpp/scratchcpp-player.svg?style=for-the-badge
[stars-url]: https://github.com/scratchcpp/scratchcpp-player/stargazers
[issues-shield]: https://img.shields.io/github/issues/scratchcpp/scratchcpp-player.svg?style=for-the-badge
[issues-url]: https://github.com/scratchcpp/scratchcpp-player/issues
[license-shield]: https://img.shields.io/github/license/scratchcpp/scratchcpp-player.svg?style=for-the-badge
[license-url]: https://github.com/scratchcpp/scratchcpp-player/blob/master/LICENSE
[product-screenshot]: res/screenshot.png
