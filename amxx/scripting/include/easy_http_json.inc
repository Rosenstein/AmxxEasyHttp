#if defined _easy_http_json_included
    #endinput
#endif
#define _easy_http_json_included

#pragma reqlib easy_http
#if !defined AMXMODX_NOAUTOLOAD
    #pragma loadlib easy_http
#endif

/*
 * JSON types
 */
enum EzJSONType
{
	EzJSONError   = -1,
	EzJSONNull    = 1,
	EzJSONString  = 2,
	EzJSONNumber  = 3,
	EzJSONObject  = 4,
	EzJSONArray   = 5,
	EzJSONBoolean = 6
};

/*
 * JSON invalid handle
 */
enum EzJSON
{
	EzInvalid_JSON = -1
}

/**
 * Helper macros for checking type
 */
#define ezjson_is_object(%1)   (%1 != EzInvalid_JSON && ezjson_get_type(%1) == EzJSONObject)
#define ezjson_is_array(%1)    (%1 != EzInvalid_JSON && ezjson_get_type(%1) == EzJSONArray)
#define ezjson_is_string(%1)   (%1 != EzInvalid_JSON && ezjson_get_type(%1) == EzJSONString)
#define ezjson_is_number(%1)   (%1 != EzInvalid_JSON && ezjson_get_type(%1) == EzJSONNumber)
#define ezjson_is_bool(%1)     (%1 != EzInvalid_JSON && ezjson_get_type(%1) == EzJSONBoolean)
#define ezjson_is_null(%1)     (%1 != EzInvalid_JSON && ezjson_get_type(%1) == EzJSONNull)
#define ezjson_is_true(%1)     (%1 != EzInvalid_JSON && ezjson_is_bool(%1) && ezjson_get_bool(%1))
#define ezjson_is_false(%1)    (%1 != EzInvalid_JSON && ezjson_is_bool(%1) && !ezjson_get_bool(%1))

/**
 * Parses JSON string or a file that contains JSON.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param string            String to parse
 * @param is_file           True to treat string param as filename, false otherwise
 * @param with_comments     True if parsing JSON includes comments (it will ignore them), false otherwise
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_parse(const string[], bool:is_file = false, bool:with_comments = false);

/**
 * Checks if the first value is the same as the second one.
 *
 * @param value1            EzJSON handle
 * @param value2            EzJSON handle
 *
 * @return                  True if they are the same, false otherwise
 * @error                   If passed value is not a valid handle
 */
native bool:ezjson_equals(const EzJSON:value1, const EzJSON:value2);

/**
 * Validates json by checking if object have identically named
 * fields with matching types.
 *
 * @note                    Schema {"name":"", "age":0} will validate
 *                          {"name":"Joe", "age":25} and {"name":"Joe", "age":25, "gender":"m"},
 *                          but not {"name":"Joe"} or {"name":"Joe", "age":"Cucumber"}.
 *
 * @note                    In case of arrays, only first value in schema
 *                          is checked against all values in tested array.
 *
 * @note                    Empty objects ({}) validate all objects,
 *                          empty arrays ([]) validate all arrays,
 *                          null validates values of every type.
 *
 * @param schema            EzJSON handle
 * @param value             EzJSON handle
 *
 * @return                  True if passed value is valid, false otherwise
 * @error                   If a schema handle or value handle is invalid
 */
native bool:ezjson_validate(const EzJSON:schema, const EzJSON:value);

/**
 * Gets value's parent handle.
 *
 * @note                  Parent's handle needs to be freed using ezjson_free() native.
 *
 * @param value           EzJSON handle
 *
 * @return                Parent's handle
 */
native EzJSON:ezjson_get_parent(const EzJSON:value);

/**
 * Gets JSON type of passed value.
 *
 * @param value             EzJSON handle
 *
 * @return                  JSON type (EzJSONType constants)
 * @error                   If a value handle is invalid
 */
native EzJSONType:ezjson_get_type(const EzJSON:value);

/**
 * Inits an empty object.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_object();

/**
 * Inits an empty array.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_array();

/**
 * Inits string data.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param value             String that the handle will be initialized with
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_string(const value[]);

/**
 * Inits a number.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param value             Integer number that the handle will be initialized with
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_number(any:value);

/**
 * Inits a real number.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param value             Real number that the handle will be initialized with
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_real(Float:value);

/**
 * Inits a boolean value.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param value             Boolean value that the handle will be initialized with
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_bool(bool:value);

/**
 * Inits a null.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 */
native EzJSON:ezjson_init_null();

/**
 * Creates deep copy of passed value.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param value             EzJSON handle to be copied
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 * @error                   If passed value is not a valid handle
 */
native EzJSON:ezjson_deep_copy(const EzJSON:value);

/**
 * Frees handle.
 *
 * @param handle            EzJSON handle to be freed
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid handle
 */
native bool:ezjson_free(&EzJSON:handle);

/**
 * Gets string data.
 *
 * @param value             EzJSON handle
 * @param buffer            Buffer to copy string to
 * @param maxlen            Maximum size of the buffer
 *
 * @return                  The number of cells written to the buffer
 * @error                   If passed value is not a valid handle
 */
native ezjson_get_string(const EzJSON:value, buffer[], maxlen);

/**
 * Gets a number.
 *
 * @param value             EzJSON handle
 *
 * @return                  Number
 * @error                   If passed value is not a valid handle
 */
native ezjson_get_number(const EzJSON:value);

/**
 * Gets a real number.
 *
 * @param value             EzJSON handle
 *
 * @return                  Real number
 * @error                   If passed value is not a valid handle
 */
native Float:ezjson_get_real(const EzJSON:value);

/**
 * Gets a boolean value.
 *
 * @param value             EzJSON handle
 *
 * @return                  Boolean value
 * @error                   If passed value is not a valid handle
 */
native bool:ezjson_get_bool(const EzJSON:value);

/**
 * Gets a value from the array.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param array             Array handle
 * @param index             Position in the array (starting from 0)
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 * @error                   If passed handle is not a valid array
 */
native EzJSON:ezjson_array_get_value(const EzJSON:array, index);

/**
 * Gets string data from the array.
 *
 * @param array             Array handle
 * @param index             Position in the array (starting from 0)
 * @param buffer            Buffer to copy string to
 * @param maxlen            Maximum size of the buffer
 *
 * @return                  The number of cells written to the buffer
 * @error                   If passed handle is not a valid array
 */
native ezjson_array_get_string(const EzJSON:array, index, buffer[], maxlen);

/**
 * Gets a number from the array.
 *
 * @param array             Array handle
 * @param index             Position in the array (starting from 0)
 *
 * @return                  The number as integer
 * @error                   If passed handle is not a valid array
 */
native ezjson_array_get_number(const EzJSON:array, index);

/**
 * Gets a real number from the array.
 *
 * @param array             Array handle
 * @param index             Position in the array (starting from 0)
 *
 * @return                  The number as float
 * @error                   If passed handle is not a valid array
 */
native Float:ezjson_array_get_real(const EzJSON:array, index);

/**
 * Gets a boolean value from the array.
 *
 * @param array             Array handle
 * @param index             Position in the array (starting from 0)
 *
 * @return                  Boolean value
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_get_bool(const EzJSON:array, index);

/**
 * Gets count of the elements in the array.
 *
 * @param array             Array handle
 *
 * @return                  Number of elements in the array
 * @error                   If passed handle is not a valid array
 */
native ezjson_array_get_count(const EzJSON:array);

/**
 * Replaces an element in the array with value.
 *
 * @param array             Array handle
 * @param index             Position in the array to be replaced
 * @param value             EzJSON handle to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_replace_value(EzJSON:array, index, const EzJSON:value);

/**
 * Replaces an element in the array with string data.
 *
 * @param array             Array handle
 * @param index             Position in the array to be replaced
 * @param string            String to copy
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_replace_string(EzJSON:array, index, const string[]);

/**
 * Replaces an element in the array with number.
 *
 * @param array             Array handle
 * @param index             Position in the array to be replaced
 * @param number            Number to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_replace_number(EzJSON:array, index, any:number);

/**
 * Replaces an element in the array with real number.
 *
 * @param array             Array handle
 * @param index             Position in the array to be replaced
 * @param number            Real number to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_replace_real(EzJSON:array, index, Float:number);

/**
 * Replaces an element in the array with boolean value.
 *
 * @param array             Array handle
 * @param index             Position in the array to be replaced
 * @param boolean           Boolean value to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_replace_bool(EzJSON:array, index, bool:boolean);

/**
 * Replaces an element in the array with null.
 *
 * @param array             Array handle
 * @param index             Position in the array to be replaced
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_replace_null(EzJSON:array, index);

/**
 * Appends a value in the array.
 *
 * @param array             Array handle
 * @param value             EzJSON handle to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_append_value(EzJSON:array, const EzJSON:value);

/**
 * Appends string data in the array.
 *
 * @param array             Array handle
 * @param string            String to copy
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_append_string(EzJSON:array, const string[]);

/**
 * Appends a number in the array.
 *
 * @param array             Array handle
 * @param number            Number to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_append_number(EzJSON:array, any:number);

/**
 * Appends a real number in the array.
 *
 * @param array             Array handle
 * @param number            Real number to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_append_real(EzJSON:array, Float:number);

/**
 * Appends a boolean value in the array.
 *
 * @param array             Array handle
 * @param boolean           Boolean value to set
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_append_bool(EzJSON:array, bool:boolean);

/**
 * Appends a null in the array.
 *
 * @param array             Array handle
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_append_null(EzJSON:array);

/**
 * Removes an element from the array.
 *
 * @note                    Order of values in array may change during execution.
 *
 * @param array             Array handle
 * @param index             Position in the array (starting from 0)
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_remove(EzJSON:array, index);

/**
 * Removes all elements from the array.
 *
 * @param array             Array handle
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid array
 */
native bool:ezjson_array_clear(EzJSON:array);

/**
 * Gets a value from the object.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 * @error                   If passed handle is not a valid object
 */
native EzJSON:ezjson_object_get_value(const EzJSON:object, const name[], bool:dot_not = false);

/**
 * Gets string data from the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param buffer            Buffer to copy string to
 * @param maxlen            Maximum size of the buffer
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  The number of cells written to the buffer
 * @error                   If passed handle is not a valid object
 */
native ezjson_object_get_string(const EzJSON:object, const name[], buffer[], maxlen, bool:dot_not = false);

/**
 * Gets a number from the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  Number
 * @error                   If passed handle is not a valid object
 */
native ezjson_object_get_number(const EzJSON:object, const name[], bool:dot_not = false);

/**
 * Gets a real number from the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  Real number
 * @error                   If passed handle is not a valid object
 */
native Float:ezjson_object_get_real(const EzJSON:object, const name[], bool:dot_not = false);

/**
 * Gets a boolean value from the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  Boolean value
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_get_bool(const EzJSON:object, const name[], bool:dot_not = false);

/**
 * Gets count of the keys in the object.
 *
 * @param object            Object handle
 *
 * @return                  Keys count
 * @error                   If passed handle is not a valid object
 */
native ezjson_object_get_count(const EzJSON:object);

/**
 * Gets name of the object's key.
 *
 * @param object            Object handle
 * @param index             Position from which get key name
 * @param buffer            Buffer to copy string to
 * @param maxlen            Maximum size of the buffer
 *
 * @return                  The number of cells written to the buffer
 * @error                   If passed handle is not a valid object
 */
native ezjson_object_get_name(const EzJSON:object, index, buffer[], maxlen);

/**
 * Gets a value at the specified position from the object.
 *
 * @note                    Needs to be freed using ezjson_free() native.
 *
 * @param object            Object handle
 * @param index             Position from which get key name
 *
 * @return                  EzJSON handle, EzInvalid_JSON if error occurred
 * @error                   If passed handle is not a valid object
 */
native EzJSON:ezjson_object_get_value_at(const EzJSON:object, index);

/**
 * Checks if the object has a value with a specific name and type.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param type              Type of value, if EzJSONError type will not be checked
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if has, false if not
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_has_value(const EzJSON:object, const name[], EzJSONType:type = EzJSONError, bool:dot_not = false);

/**
 * Sets a value in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 * @note                    It also removes the old value if any.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param value             EzJSON handle to set
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_set_value(EzJSON:object, const name[], const EzJSON:value, bool:dot_not = false);

/**
 * Sets string data in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 * @note                    It also removes the old value if any.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param string            String to copy
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_set_string(EzJSON:object, const name[], const string[], bool:dot_not = false);

/**
 * Sets a number in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 * @note                    It also removes the old value if any.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param number            Number to set
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_set_number(EzJSON:object, const name[], any:number, bool:dot_not = false);

/**
 * Sets a real number in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 * @note                    It also removes the old value if any.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param number            Real number to set
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_set_real(EzJSON:object, const name[], Float:number, bool:dot_not = false);

/**
 * Sets a boolean value in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 * @note                    It also removes the old value if any.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param boolean           Boolean value to set
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_set_bool(EzJSON:object, const name[], bool:boolean, bool:dot_not = false);

/**
 * Sets a null in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 * @note                    It also removes the old value if any.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_set_null(EzJSON:object, const name[], bool:dot_not = false);

/**
 * Removes a key and its value in the object.
 *
 * @note                    If dot notation is used some values may be inaccessible
 *                          because valid names in JSON can contain dots.
 *
 * @param object            Object handle
 * @param name              Key name
 * @param dot_not           True to use dot notation, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_remove(EzJSON:object, const name[], bool:dot_not = false);

/**
 * Removes all keys and their values in the object.
 *
 * @param object            Object handle
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid object
 */
native bool:ezjson_object_clear(EzJSON:object);

/**
 * Gets size of serialization.
 *
 * @param value             EzJSON handle
 * @param pretty            True to count size for pretty format, false to not
 * @param null_byte         True to include null byte, false to not
 *
 * @return                  Size of serialized string
 * @error                   If passed handle is not a valid value
 */
native ezjson_serial_size(const EzJSON:value, bool:pretty = false, bool:null_byte = false);

/**
 * Copies serialized string to the buffer.
 *
 * @param value             EzJSON handle
 * @param buffer            Buffer to copy string to
 * @param maxlen            Maximum size of the buffer
 * @param pretty            True to format pretty JSON string, false to not
 *
 * @return                  The number of cells written to the buffer
 * @error                   If passed handle is not a valid value
 */
native ezjson_serial_to_string(const EzJSON:value, buffer[], maxlen, bool:pretty = false);

/**
 * Copies serialized string to the file.
 *
 * @param value             EzJSON handle
 * @param file              Path to the file
 * @param pretty            True to format pretty JSON string, false to not
 *
 * @return                  True if succeed, false otherwise
 * @error                   If passed handle is not a valid value
 */
native bool:ezjson_serial_to_file(const EzJSON:value, const file[], bool:pretty = false);
