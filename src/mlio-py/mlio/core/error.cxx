/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not use this file except in compliance with the License. A copy of
 * the License is located at
 *
 *      http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#include "module.h"

namespace py = pybind11;

using namespace mlio;

namespace pymlio {

void
register_exceptions(py::module &m)
{
    PyObject *base;

    base = py::register_exception<stream_error>(
               m, "StreamError", ::PyExc_RuntimeError)
               .ptr();
    py::register_exception<inflate_error>(m, "InflateError", base);

    base = py::register_exception<corrupt_record_error>(
               m, "CorruptRecordError", ::PyExc_RuntimeError)
               .ptr();
    py::register_exception<corrupt_footer_error>(
        m, "CorruptFooterError", base);
    py::register_exception<corrupt_header_error>(
        m, "CorruptHeaderError", base);

    py::register_exception<record_too_large_error>(
        m, "RecordTooLargeError", ::PyExc_RuntimeError);

    base = py::register_exception<data_reader_error>(
               m, "DataReaderError", ::PyExc_RuntimeError)
               .ptr();
    py::register_exception<schema_error>(m, "SchemaError", base);
    py::register_exception<invalid_instance_error>(
        m, "InvalidInstanceError", base);

    py::register_exception<field_too_large_error>(
        m, "FieldTooLargeError", ::PyExc_RuntimeError);

    py::register_exception<not_supported_error>(
        m, "NotSupportedError", ::PyExc_RuntimeError);
}

}  // namespace pymlio
