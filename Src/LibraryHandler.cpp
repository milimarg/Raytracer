/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** LibraryHandler
*/

#include "LibraryHandler.hpp"

namespace rtx
{
    LibraryHandler::LibraryHandler(const std::string &filename) : _libraryHandle(nullptr)
    {
        _libraryHandle = dlopen(filename.c_str(), RTLD_LAZY);

        if (!_libraryHandle)
            throw Error("LibraryHandler - LibraryHandler" + std::string(dlerror()));
    }

    LibraryHandler::~LibraryHandler()
    {
        close();
    }

    bool LibraryHandler::isOpen() const
    {
        return _libraryHandle != nullptr;
    }

    std::string LibraryHandler::getLastError() const
    {
        const char *error = dlerror();

        return error ? std::string(error) : std::string();
    }

    void LibraryHandler::close()
    {
        if (_libraryHandle) {
            dlclose(_libraryHandle);
            _libraryHandle = nullptr;
        }
    }
}
