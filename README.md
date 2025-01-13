<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![CC0 1.0 Universal][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/pgodschalk/raytracing">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">@pgodschalk/raytracing</h3>

  <p align="center">
    Learning ray tracing in C++17
    <br />
    <a href="https://github.com/pgodschalk/raytracing/blob/main/docs/progress-over-time.md"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/pgodschalk/raytracing/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/pgodschalk/raytracing/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About the project</a>
      <ul>
        <li><a href="#built-with">Built with</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About the project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

My implementation of learning ray tracing in C++17. This project is based on
the book
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built with

* [![C++][cpp]][cpp-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting started

To get a local copy up and running follow these simple example steps.

### Prerequisites

* [CMake](https://cmake.org)
  ```sh
  asdf plugin add cmake https://github.com/asdf-community/asdf-cmake.git
  asdf install cmake 3.31.3 && asdf global cmake 3.31.3
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/pgodschalk/raytracing.git
   ```
2. Create a build dir
   ```sh
   mkdir -p build
   ```
4. Compile the binary
   ```sh
   cmake -DCMAKE_BUILD_TYPE=Release -B build/
   cmake --build build/
   ```
5. Change git remote url to avoid accidental pushes to base project
   ```sh
   git remote set-url origin pgodschalk/raytracing
   git remote -v # confirm the changes
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

```sh
./build/bin/RaytracingExecutable >! out.ppm
```

Use a PPM viewer to view the output. On MacOS you can use the built-in
`open` command to view the image.

```sh
open out.ppm
```

_For more examples, please refer to the [Documentation](https://github.com/pgodschalk/raytracing/blob/main/docs/progress-over-time.md)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/pgodschalk/raytracing/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Top contributors:

<a href="https://github.com/pgodschalk/raytracing/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=pgodschalk/raytracing" alt="contrib.rocks image" />
</a>

<!-- LICENSE -->
## License

Distributed under the CC0 1.0 Universal. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Patrick Godschalk - [@kernelpanics.nl](https://bsky.app/profile/kernelpanics.nl) - patrick@kernelpanics.nl

Project Link: [https://github.com/pgodschalk/raytracing](https://github.com/pgodschalk/raytracing)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/pgodschalk/raytracing.svg?style=for-the-badge
[contributors-url]: https://github.com/pgodschalk/raytracing/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/pgodschalk/raytracing.svg?style=for-the-badge
[forks-url]: https://github.com/pgodschalk/raytracing/network/members
[stars-shield]: https://img.shields.io/github/stars/pgodschalk/raytracing.svg?style=for-the-badge
[stars-url]: https://github.com/pgodschalk/raytracing/stargazers
[issues-shield]: https://img.shields.io/github/issues/pgodschalk/raytracing.svg?style=for-the-badge
[issues-url]: https://github.com/pgodschalk/raytracing/issues
[license-shield]: https://img.shields.io/github/license/pgodschalk/raytracing?style=for-the-badge
[license-url]: https://github.com/pgodschalk/raytracing/blob/main/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/patrick-godschalk
[product-screenshot]: images/screenshot.gif
[cpp]: https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white
[cpp-url]: https://isocpp.org
