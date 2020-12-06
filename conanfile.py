from conans import ConanFile, CMake, tools
# from parktoma.vscconan import update_cpp_tools


class DataStructuresConan(ConanFile):
    name = "data_structures"
    version = "0.1"
    generators = "cmake"

    exports_sources = "../src**"
    no_copy_source = True

    def requirements(self):
        self.requires("fmt/7.1.2")
        self.requires("range-v3/0.11.0")
        self.requires("catch2/2.13.2")

    def configure(self):
        return super().configure()

    def build(self):
        cmake = CMake(self, build_type="Debug")
        cmake.configure(source_folder="tests")
        cmake.build()

    def package(self):
        self.copy("*.hpp", dst="include/data_structures", src="src")
        pass
