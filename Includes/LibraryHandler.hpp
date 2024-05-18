/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** LibraryHandler
*/

#ifndef LIBRARYHANDLER_HPP_
    #define LIBRARYHANDLER_HPP_
    #include "ILibraryHandler.hpp"
    #include "Error/Error.hpp"

namespace rtx
{
    /**
     * LibraryHandler Class
     */
    class LibraryHandler : public ILibraryHandler {
        public:
            /**
             * Load a library
             * @param filename path to library
             */
            explicit LibraryHandler(const std::string &filename);

            ~LibraryHandler();

            /**
             *
             * @tparam T type of returned symbol
             * @param symbolName name of the symbol
             * @return symbol in lib
             */
            template<typename T>
            T getSymbol(const std::string &symbolName);

            /**
             *
             * @return is the lib still open?
             */
            bool isOpen() const override;

            /**
             *
             * @return last thrown error by dlerror()
             */
            std::string getLastError() const override;

            /**
             * close library
             */
            void close() override;

        private:
            void *_libraryHandle;
    };

    template<typename T>
    T LibraryHandler::getSymbol(const std::string &symbolName)
    {
        if (!_libraryHandle) {
            throw Error("LibraryHandler - getSymbol - Library not loaded");
        }

        void *symbol = dlsym(_libraryHandle, symbolName.c_str());
        if (!symbol) {
            throw Error("LibraryHandler - getSymbol - Symbol not found");
        }

        using function_type = T (*)();
        auto *function = reinterpret_cast<function_type>(symbol);

        return function();
    }
}

#endif /* !LIBRARYHANDLER_HPP_ */
