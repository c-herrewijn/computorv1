#!/usr/bin/env python3

import sys
from pathlib import Path


HPP_TEMPLATE = """#ifndef {CLASS_ALL_CAPS}_H
# define {CLASS_ALL_CAPS}_H

#include <string>

class {CLASS} {
public:
    {CLASS}();
    {CLASS}(const {CLASS} &obj);
    ~{CLASS}();
    {CLASS} &operator=(const {CLASS} &obj);

private:

};

#endif
"""


CPP_TEMPLATE = """#include "{CLASS_SNAKE}.hpp"

{CLASS}::{CLASS}() {}
{CLASS}::~{CLASS}() {}
{CLASS}::{CLASS}(const {CLASS} &obj) {
    *this = obj;
}

// TODO: define assignment operator
{CLASS} &{CLASS}::operator=(const {CLASS} &obj)
{
    // NOTE: the assignment operator can not set const attributes!
    // this->_attr1 = obj._attr1;
    return *this;
}

"""


def to_pascal_case(in_str: str) -> str:
    return "".join(
        (
            ""
            if char == "_"
            else (char.upper() if (idx == 0 or in_str[idx - 1] == "_") else char)
        )
        for idx, char in enumerate(in_str)
    )


# add underscore before upper case char for every case-change in the string
def to_snake_case(str: str) -> str:
    return "".join(
        (
            f"_{char.lower()}"
            if (str[idx].isupper() and idx != 0 and str[idx - 1] != "_")
            and (
                str[idx - 1].islower()
                or (idx < len(str) - 1 and str[idx + 1].islower())
            )
            else char.lower()
        )
        for idx, char in enumerate(str)
    )


def create_class(arg: str):
    class_pascal_case = to_pascal_case(arg)
    class_snake_case = to_snake_case(arg)
    class_caps_with_underscores = class_snake_case.upper()

    # create hpp file
    hpp_file_name = f"{class_snake_case}.hpp"
    hpp_text = HPP_TEMPLATE.replace(
        "{CLASS_ALL_CAPS}", class_caps_with_underscores).replace(
        "{CLASS}", class_pascal_case
    )
    Path(hpp_file_name).write_text(hpp_text)

    # create cpp file
    cpp_file_name = f"{class_snake_case}.cpp"
    cpp_text = CPP_TEMPLATE.replace(
        "{CLASS_SNAKE}", class_snake_case).replace(
        "{CLASS}", class_pascal_case
    )
    Path(cpp_file_name).write_text(cpp_text)

    print(f"created files for class {class_pascal_case}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("provide class name as argument")
    create_class(sys.argv[1])
