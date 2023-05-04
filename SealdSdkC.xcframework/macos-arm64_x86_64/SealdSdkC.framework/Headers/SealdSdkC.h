#ifndef LIB_SEALD_SDK_H
#define LIB_SEALD_SDK_H

// Helper SealdStringArray

/**
 * SealdStringArray holds an array of strings.
 */
typedef struct SealdStringArray SealdStringArray;

/**
 * SealdStringArray_New instantiates a new SealdStringArray.
 *
 * @return The newly created SealdStringArray.
 */
SealdStringArray* SealdStringArray_New();

/**
 * SealdStringArray_Free frees the memory allocated for the SealdStringArray itself, and all strings contained therein.
 *
 * @param array The SealdStringArray to free.
 */
void SealdStringArray_Free(SealdStringArray* array);

/**
 * SealdStringArray_Add adds a given string to the array.
 * SealdStringArray_Add does *not* take ownership of the given string. It creates a copy for itself.
 *
 * @param array The SealdStringArray to add a string to.
 * @param s The string to add.
 */
void SealdStringArray_Add(SealdStringArray* array, char* s);

/**
 * SealdStringArray_Get returns the string at position i.
 * The caller is responsible for calling `free` on this returned string when no longer necessary.
 *
 * @param array The SealdStringArray from which to retrieve an element.
 * @param i The position from which we want to retrieve the string.
 * @return The string at position i.
 */
char* SealdStringArray_Get(SealdStringArray* array, int i);

/**
 * SealdStringArray_Size returns the size of the given SealdStringArray.
 *
 * @param array The SealdStringArray for which to retrieve the size.
 * @return The size of the given SealdStringArray.
 */
int SealdStringArray_Size(SealdStringArray* array);


// Helper SealdClearFile

/**
 * SealdClearFile represents a decrypted file.
 */
typedef struct {
    /** The filename of the decrypted file */
    char* Filename;
    /** The ID of the EncryptionSession to which this file belongs */
    char* SessionId;
    /** The content of the decrypted file */
    unsigned char* FileContent;
    /** The length of FileContent */
    int FileContentLen;
} SealdClearFile;

/**
 * SealdClearFile_Free is a helper to free a SealdClearFile instance and all fields within.
 *
 * @param cf The SealdClearFile to free.
 */
void SealdClearFile_Free(SealdClearFile* cf);


// Helper SealdAccountInfo

/**
 * SealdAccountInfo is returned when calling SealdSdk_createAccount or SealdSdk_getCurrentAccountInfo,
 * containing information about the local account.
 */
typedef struct {
    /** The ID of the current user for this SDK instance. */
    char* UserId;
    /** The ID of the current device for this SDK instance. */
    char* DeviceId;
} SealdAccountInfo;

/**
 * SealdAccountInfo_Free is a helper to free a SealdAccountInfo instance and all fields within.
 *
 * @param info The SealdAccountInfo to free.
 */
void SealdAccountInfo_Free(SealdAccountInfo* info);


// Helper SealdInitializeOptions

/**
 * SealdInitializeOptions is the main options object for initializing the SDK instance
 */
typedef struct {
    /** ApiURL is the Seald server for this instance to use. This value is given on your Seald dashboard. */
    char* ApiURL;
    /** AppId is the ID given by the Seald server to your app. This value is given on your Seald dashboard. */
    char* AppId;
    /** KeySize is the Asymmetric key size for newly generated keys. Defaults to 4096. Warning: for security, it is extremely not recommended to lower this value. For advanced use only. */
    int KeySize;
    /** DbPath is the path where to store the local Seald database. */
    char* DbPath;
    /** EncryptionSessionCacheTTL is the duration of cache lifetime in Milliseconds. `-1` to cache forever. `0` for no cache. */
    long long EncryptionSessionCacheTTL;
    /** LogLevel is the minimum level of logs you want. All logs of this level or above will be displayed. `-1`: Trace; `0`: Debug; `1`: Info; `2`: Warn; `3`: Error; `4`: Fatal; `5`: Panic; `6`: NoLevel; `7`: Disabled. */
    signed char LogLevel;
    /** LogNoColor should be set to `0` if you want to enable colors in the log output, `1` if you don't. */
    int LogNoColor;
    /** InstanceName is an arbitrary name to give to this Seald instance. Can be useful for debugging when multiple instances are running in parallel, as it is added to logs. */
    char* InstanceName;
    /** DatabaseEncryptionKeyB64 is the encryption key with which to encrypt the local Seald database. This **must** be the Base64 string encoding of a cryptographically random buffer of 64 bytes. */
    char* DatabaseEncryptionKeyB64;
} SealdInitializeOptions;


// Helper SealdCreateSubIdentityResponse

/**
 * SealdCreateSubIdentityResponse represents a newly created sub identity.
 */
typedef struct {
    /** The ID of the newly created device. */
    char* DeviceId;
    /** The identity export of the newly created sub-identity. */
    unsigned char* BackupKey;
    /** The length of BackupKey. */
    int BackupKeyLen;
} SealdCreateSubIdentityResponse;

/**
 * SealdCreateSubIdentityResponse_Free is a helper to free a SealdCreateSubIdentityResponse instance and all fields within.
 *
 * @param resp The SealdCreateSubIdentityResponse to free.
 */
void SealdCreateSubIdentityResponse_Free(SealdCreateSubIdentityResponse* resp);


// Helper SealdConnector

/**
 * SealdConnector represents all details about a connector.
 */
typedef struct {
    char* SealdId;
    char* Type;
    char* Value;
    char* Id;
    char* State;
} SealdConnector;

/**
 * SealdConnector_Free is a helper to free a SealdConnector instance and all fields within.
 *
 * @param c The SealdConnector to free.
 */
void SealdConnector_Free(SealdConnector* c);


// Helper SealdConnectorsArray

/**
 * SealdConnectorsArray holds an array of SealdConnector instances.
 */
typedef struct SealdConnectorsArray SealdConnectorsArray;

/**
 * SealdConnectorsArray_New instantiates a new SealdConnectorsArray.
 *
 * @return The newly created SealdConnectorsArray.
 */
SealdConnectorsArray* SealdConnectorsArray_New();

/**
 * SealdConnectorsArray_Free frees the memory allocated for the SealdConnectorsArray itself, and all SealdConnector instances contained therein.
 *
 * @param array The SealdConnectorsArray to free.
 */
void SealdConnectorsArray_Free(SealdConnectorsArray* array);

/**
 * SealdConnectorsArray_Add adds a given SealdConnector instance to the array.
 * SealdConnectorsArray_Add *takes ownership* of the given SealdConnector.
 * The caller *must not* use it anymore, and must not call `free` on it.
 *
 * @param array The SealdConnectorsArray to add a SealdConnector instance to.
 * @param c The SealdConnector instance to add.
 */
void SealdConnectorsArray_Add(SealdConnectorsArray* array, SealdConnector* c);

/**
 * SealdConnectorsArray_Get returns a reference to the SealdConnector instance at position i.
 * The caller *must not* call `free` on it.
 *
 * @param array The SealdConnectorsArray from which to retrieve an element.
 * @param i The position from which we want to retrieve the SealdConnector instance.
 * @return The SealdConnector instance at position i.
 */
SealdConnector* SealdConnectorsArray_Get(SealdConnectorsArray* array, int i);

/**
 * SealdConnectorsArray_Size returns the size of the given SealdConnectorsArray.
 *
 * @param array The SealdConnectorsArray for which to retrieve the size.
 * @return The size of the given SealdConnectorsArray.
 */
int SealdConnectorsArray_Size(SealdConnectorsArray* array);


// Helper SealdConnectorTypeValueArray

/**
 * SealdConnectorTypeValueArray holds an array of connector type-value pairs.
 */
typedef struct SealdConnectorTypeValueArray SealdConnectorTypeValueArray;

/**
 * SealdConnectorTypeValueArray_New instantiates a new SealdConnectorTypeValueArray.
 *
 * @return The newly created SealdConnectorTypeValueArray.
 */
SealdConnectorTypeValueArray* SealdConnectorTypeValueArray_New();

/**
 * SealdConnectorTypeValueArray_Free frees the memory allocated for the SealdConnectorTypeValueArray itself, and all connector type-value pairs contained therein.
 *
 * @param array The SealdConnectorTypeValueArray to free.
 */
void SealdConnectorTypeValueArray_Free(SealdConnectorTypeValueArray* array);

/**
 * SealdConnectorTypeValueArray_Add adds a given connector type-value pair to the array.
 * SealdConnectorTypeValueArray_Add *does not take ownership* of the given strings. It creates copies for itself.
 *
 * @param array The SealdConnectorTypeValueArray to add a connector type-value pair to.
 * @param connectorType The connector type to add.
 * @param connectorValue The connector value to add.
 */
void SealdConnectorTypeValueArray_Add(SealdConnectorTypeValueArray* array, char* connectorType, char* connectorValue);

/**
 * SealdConnectorTypeValueArray_Get returns the connector type-value pair at position i.
 * The caller is responsible for calling `free` on the returned type and value when no longer necessary.
 *
 * @param array The SealdConnectorTypeValueArray from which to retrieve a connector type-value pair.
 * @param i The position from which we want to retrieve the connector type-value pair.
 * @param connectorType A pointer to which to write the connector type at position i.
 * @param connectorValue A pointer to which to write the connector value at position i.
 */
void SealdConnectorTypeValueArray_Get(SealdConnectorTypeValueArray* array, int i, char** connectorType, char** connectorValue);

/**
 * SealdConnectorTypeValueArray_Size returns the size of the given SealdConnectorTypeValueArray.
 *
 * @param array The SealdConnectorTypeValueArray for which to retrieve the size.
 * @return The size of the given SealdConnectorTypeValueArray.
 */
int SealdConnectorTypeValueArray_Size(SealdConnectorTypeValueArray* array);


// Helper SealdPreValidationToken

/**
 * SealdPreValidationToken represents a way for your server to authorize the adding of a connector.
 */
typedef struct {
    char* DomainValidationKeyId;
    char* Nonce;
    char* Token;
} SealdPreValidationToken;

/**
 * SealdPreValidationToken_Free is a helper to free a SealdPreValidationToken instance and all fields within.
 *
 * @param t The SealdPreValidationToken to free.
 */
void SealdPreValidationToken_Free(SealdPreValidationToken* t);


// Helper SealdMassReencryptOptions

/**
 * SealdMassReencryptOptions represents options for SealdSdk_MassReencrypt.
 */
typedef struct {
    /** Number of times to retry. Defaults to 3. */
    int Retries;
    /** Default to 1000. */
    int RetrieveBatchSize;
    /** Time to wait between retries, in Milliseconds. Defaults to 3 seconds. */
    long long WaitBetweenRetries;
    /** Whether to wait for provisioning (new behaviour) or not. `1` to wait, `0` to not wait. Defaults to `1`. */
    int WaitProvisioning; // bool
    /** Time to wait if device is not provisioned on the server yet, in Milliseconds. The actual wait time will be increased on subsequent tries, by `WaitProvisioningTimeStep`, up to `WaitProvisioningTimeMax`. Defaults to 5 seconds. */
    long long WaitProvisioningTime;
    /** Maximum time to wait if device is not provisioned on the server yet, in Milliseconds. Defaults to 10 seconds. */
    long long WaitProvisioningTimeMax;
    /** Amount to increase the time to wait if device is not provisioned on the server yet, in Milliseconds. Defaults to 1 second. */
    long long WaitProvisioningTimeStep;
    /** Maximum number of tries to check if the device is provisioned yet. Defaults to 100. */
    int WaitProvisioningRetries;
    /** Whether to update the local account before trying the reencryption. `1` to update, `0` to not update. Defaults to `0`. */
    int ForceLocalAccountUpdate; // bool
} SealdMassReencryptOptions;

/**
 * Initialize a SealdMassReencryptOptions instance with default values.
 */
SealdMassReencryptOptions SealdMassReencryptOptions_Defaults();


// Helper SealdMassReencryptResponse

/**
 * SealdMassReencryptResponse represents the results of a call to [SealdSdk.massReencrypt].
 */
typedef struct {
    /** The number of session keys that were reencrypted for the given device. */
    int Reencrypted;
    /** The number of session keys that could not be reencrypted for the given device. */
    int Failed;
} SealdMassReencryptResponse;


// Helper SealdDeviceMissingKeys

/**
 * SealdDeviceMissingKeys represents a device of the current account which is missing some keys,
 * and for which you probably want to call SealdSdk_MassReencrypt.
 */
typedef struct {
    /** The ID of the device which is missing some keys. */
    char* DeviceId;
    /** The number of keys missing for this device. Warning: the count may be lower than reality if the device was recently created, as the server may still be provisioning keys for this device. In that case, you can still call SealdSdk_MassReencrypt for that device. */
    int Count;
} SealdDeviceMissingKeys;

/**
 * SealdDeviceMissingKeys_Free frees the memory allocated for the SealdDeviceMissingKeys itself, and all fields within.
 *
 * @param d The SealdDeviceMissingKeys to free.
 */
void SealdDeviceMissingKeys_Free(SealdDeviceMissingKeys* d);


// Helper SealdDeviceMissingKeysArray

/**
 * SealdDeviceMissingKeysArray holds an array of SealdDeviceMissingKeys instances.
 */
typedef struct SealdDeviceMissingKeysArray SealdDeviceMissingKeysArray;

/**
 * SealdDeviceMissingKeysArray_New instantiates a new SealdDeviceMissingKeysArray.
 *
 * @return The newly created SealdDeviceMissingKeysArray.
 */
SealdDeviceMissingKeysArray* SealdDeviceMissingKeysArray_New();

/**
 * SealdDeviceMissingKeysArray_Free frees the memory allocated for the SealdDeviceMissingKeysArray itself, and all SealdDeviceMissingKeys instances contained therein.
 *
 * @param array The SealdDeviceMissingKeysArray to free.
 */
void SealdDeviceMissingKeysArray_Free(SealdDeviceMissingKeysArray* array);

/**
 * SealdDeviceMissingKeysArray_Add adds a given SealdDeviceMissingKeys instance to the array.
 * SealdDeviceMissingKeysArray_Add *takes ownership* of the given SealdDeviceMissingKeys.
 * The caller *must not* use it anymore, and must not call `free` on it.
 *
 * @param array The SealdDeviceMissingKeysArray to add a SealdDeviceMissingKeys instance to.
 * @param d The SealdDeviceMissingKeys instance to add.
 */
void SealdDeviceMissingKeysArray_Add(SealdDeviceMissingKeysArray* array, SealdDeviceMissingKeys* d);

/**
 * SealdDeviceMissingKeysArray_Get returns a reference to the SealdDeviceMissingKeys instance at position i.
 * The caller *must not* call `free` on it.
 *
 * @param array The SealdDeviceMissingKeysArray from which to retrieve an element.
 * @param i The position from which we want to retrieve the SealdDeviceMissingKeys instance.
 * @return The SealdDeviceMissingKeys instance at position i.
 */
SealdDeviceMissingKeys* SealdDeviceMissingKeysArray_Get(SealdDeviceMissingKeysArray* array, int i);

/**
 * SealdDeviceMissingKeysArray_Size returns the size of the given SealdDeviceMissingKeysArray.
 *
 * @param array The SealdDeviceMissingKeysArray for which to retrieve the size.
 * @return The size of the given SealdDeviceMissingKeysArray.
 */
int SealdDeviceMissingKeysArray_Size(SealdDeviceMissingKeysArray* array);


// Class Encryption Session

/**
 * SealdEncryptionSession represents an encryption session, with which you can then encrypt / decrypt multiple messages.
 * This should not be created directly, and should be retrieved with SealdSdk_RetrieveEncryptionSession
 * or SealdSdk_RetrieveEncryptionSessionFromMessage.
 */
typedef struct SealdEncryptionSession SealdEncryptionSession;

/**
 * SealdEncryptionSession_Free frees the memory allocated for the SealdEncryptionSession.
 *
 * @param es The Encryption Session to free
 */
void SealdEncryptionSession_Free(SealdEncryptionSession* es);

/**
 * SealdEncryptionSession_Id returns the session ID of this encryption session.
 *
 * @param es The encryption session instance for which to return the session ID.
 * @return The session ID of the given encryption session instance. The caller must call `free` on this when no longer needed.
 */
char* SealdEncryptionSession_Id(SealdEncryptionSession* es);

/**
 * Revoke some recipients from this session.
 * If you want to revoke all recipients, see SealdEncryptionSession_RevokeAll instead.
 * If you want to revoke all recipients besides yourself, see SealdEncryptionSession_RevokeOthers.
 *
 * @param es The SealdEncryptionSession instance.
 * @param recipients The Seald IDs of users to revoke from this session.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_RevokeRecipients(SealdEncryptionSession* es, SealdStringArray* recipients, char** errMsg);

/**
 * Revoke this session entirely.
 *
 * @param es The SealdEncryptionSession instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_RevokeAll(SealdEncryptionSession* es, char** errMsg);

/**
 * Revoke all recipients besides yourself from this session.
 *
 * @param es The SealdEncryptionSession instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_RevokeOthers(SealdEncryptionSession* es, char** errMsg);

/**
 * Add new recipients to this session.
 * These recipients will be able to read all encrypted messages of this session.
 *
 * @param es The SealdEncryptionSession instance.
 * @param recipients The Seald IDs of users to add to this session.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_AddRecipients(SealdEncryptionSession* es, SealdStringArray* recipients, char** errMsg);

/**
 * Encrypt a clear-text string into an encrypted message, for the recipients of this session.
 *
 * @param es The SealdEncryptionSession instance.
 * @param clearMessage The message to encrypt.
 * @param result A pointer to which to write the resulting encrypted message.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_EncryptMessage(SealdEncryptionSession* es, char* clearMessage, char** result, char** errMsg);

/**
 * Decrypt an encrypted message string into the corresponding clear-text string.
 *
 * @param es The SealdEncryptionSession instance.
 * @param encryptedMessage The encrypted message to decrypt.
 * @param result A pointer to which to write the resulting decrypted message.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_DecryptMessage(SealdEncryptionSession* es, char* encryptedMessage, char** result, char** errMsg);

/**
 * Encrypt a clear-text file into an encrypted file, for the recipients of this session.
 *
 * @param es The SealdEncryptionSession instance.
 * @param clearFile An array of bytes of the clear-text content of the file to encrypt.
 * @param clearFileLen The length of clearFile.
 * @param filename The name of the file to encrypt.
 * @param result A pointer to which to write the resulting encrypted file.
 * @param resultLen A pointer to which to write the length of result.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_EncryptFile(SealdEncryptionSession* es, unsigned char* clearFile, int clearFileLen, char* filename, unsigned char** result, int* resultLen, char** errMsg);

/**
 * Decrypts an encrypted file into the corresponding clear-text file.
 *
 * @param es The SealdEncryptionSession instance.
 * @param encryptedFile An array of bytes of the content of the encrypted file to decrypt.
 * @param encryptedFileLen The length of encryptedFile.
 * @param result A pointer to a SealdClearFile* to store the resulting decrypted file.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_DecryptFile(SealdEncryptionSession* es, unsigned char* encryptedFile, int encryptedFileLen, SealdClearFile** result, char** errMsg);

/**
 * Encrypt a clear-text file into an encrypted file, for the recipients of this session.
 *
 * @param es The SealdEncryptionSession instance.
 * @param clearFilePath The path of the file to encrypt.
 * @param result A pointer to a char pointer where the path of the encrypted file will be stored.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_EncryptFileFromPath(SealdEncryptionSession* es, char* clearFilePath, char** result, char** errMsg);

/**
 * Decrypts an encrypted file into the corresponding clear-text file.
 *
 * @param es The SealdEncryptionSession instance.
 * @param encryptedFilePath The path of the file to encrypted file to decrypt.
 * @param result A pointer to a char pointer where the path of the decrypted file will be stored.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdEncryptionSession_DecryptFileFromPath(SealdEncryptionSession* es, char* encryptedFilePath, char** result, char** errMsg);

// Class SDK

/**
 * This is the main class for the Seald SDK. It represents an instance of the Seald SDK.
 */
typedef struct SealdSdk SealdSdk;

/**
 * Initialize a Seald SDK Instance.
 *
 * @param options A pointer to a SealdInitializeOptions instance.
 * @param result A pointer to a SealdSdk* to store the created SDK instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_Initialize(SealdInitializeOptions* options, SealdSdk** result, char** errMsg);

/**
 * Close the current SDK instance. This frees any lock on the current database, and frees the memory.
 * After calling close, the instance cannot be used anymore.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_Close(SealdSdk* sealdSdk, char** errMsg);

/* Account */

/**
 * Create a new Seald SDK Account for this Seald SDK instance.
 * This function can only be called if the current SDK instance does not have an account yet.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param displayName A name for the user to create. This is metadata, useful on the Seald Dashboard for recognizing this user.
 * @param deviceName A name for the device to create. This is metadata, useful on the Seald Dashboard for recognizing this device.
 * @param signupJwt The JWT to allow this SDK instance to create an account.
 * @param expireAfter The duration during which the created device key will be valid without renewal, in Milliseconds. Optional, defaults to 5 years.
 * @param result A pointer to SealdAccountInfo*, to store a SealdAccountInfo instance containing the Seald ID of the newly created Seald user, and the device ID.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_CreateAccount(SealdSdk* sealdSdk, char* displayName, char* deviceName, char* signupJwt, long long expireAfter, SealdAccountInfo** result, char** errMsg);

/**
 * Return information about the current account, or `NULL` if there is none.
 *
 * @param sealdSdk The SealdSdk instance.
 * @return A SealdAccountInfo instance, containing the Seald ID of the local Seald user, and the device ID, or `NULL` if there is no local user.
 */
SealdAccountInfo* SealdSdk_GetCurrentAccountInfo(SealdSdk* sealdSdk);

/**
 * Renew the keys of the current device, extending their validity.
 * If the current device has expired, you will need to call SealdSdk_RenewKeys before you are able to do anything else.
 * Warning: if the identity of the current device is stored externally, for example on SSKS,
 * you will want to re-export it and store it again, otherwise the previously stored identity will not be recognized anymore.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param keyExpireAfter The duration during which the renewed device key will be valid without further renewal, in Milliseconds. Optional, defaults to 5 years.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RenewKeys(SealdSdk* sealdSdk, long long keyExpireAfter, char** errMsg);

/**
 * Create a new sub-identity, or new device, for the current user account.
 * After creating this new device, you will probably want to call SealdSdk_MassReencrypt,
 * so that the newly created device will be able to decrypt EncryptionSessions previously created for this account.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param deviceName An optional name for the device to create. This is metadata, useful on the Seald Dashboard for recognizing this device. Optional.
 * @param expireAfter The duration during which the device key for the device to create will be valid without renewal, in Milliseconds. Optional, defaults to 5 years.
 * @param result A pointer to store a CreateSubIdentityResponse* instance, containing `DeviceId` (the ID of the newly created device), `BackupKey` (the identity export of the newly created sub-identity), and `BackupKeyLen` (the length of `BackupKey`).
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_CreateSubIdentity(SealdSdk* sealdSdk, char* deviceName, long long expireAfter, SealdCreateSubIdentityResponse** result, char** errMsg);

/**
 * Load an identity export into the current SDK instance.
 * This function can only be called if the current SDK instance does not have an account yet.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param identity The identity export that this SDK instance should import.
 * @param identityLen The length of identity.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_ImportIdentity(SealdSdk* sealdSdk, unsigned char* identity, int identityLen, char** errMsg);

/**
 * Export the current device as an identity export.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param result A pointer where to store the identity export of the current identity of this SDK instance.
 * @param resultLen A pointer where to store the result length.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_ExportIdentity(SealdSdk* sealdSdk, unsigned char** result, int* resultLen, char** errMsg);

/**
 * Push a given JWT to the Seald server, for example to add a connector to the current account.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param jwt The JWT to push.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_PushJWT(SealdSdk* sealdSdk, char* jwt, char** errMsg);

/**
 * Just call the Seald server, without doing anything.
 * This may be used for example to verify that the current instance has a valid identity.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_Heartbeat(SealdSdk* sealdSdk, char** errMsg);

/* Groups */

/**
 * Create a group, and returns the created group's ID.
 * `admins` must also be members.
 * `admins` must include yourself.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param groupName A name for the group. This is metadata, useful on the Seald Dashboard for recognizing this user.
 * @param members The Seald IDs of the members to add to the group. Must include yourself.
 * @param admins The Seald IDs of the members to also add as group admins. Must include yourself.
 * @param groupId A pointer where to store the ID of the created group.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_CreateGroup(SealdSdk* sealdSdk, char* groupName, SealdStringArray* members, SealdStringArray* admins, char** groupId, char** errMsg);

/**
 * Add members to a group.
 * Can only be done by a group administrator.
 * Can also specify which of these newly added group members should also be admins.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param groupId The group in which to add members.
 * @param membersToAdd The Seald IDs of the members to add to the group.
 * @param adminsToSet The Seald IDs of the newly added members to also set as group admins.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_AddGroupMembers(SealdSdk* sealdSdk, char* groupId, SealdStringArray* membersToAdd, SealdStringArray* adminsToSet, char** errMsg);

/**
 * Remove members from the group.
 * Can only be done by a group administrator.
 * You should call SealdSdk_RenewGroupKey() after this.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param groupId The group from which to remove members.
 * @param membersToRemove The Seald IDs of the members to remove from the group.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RemoveGroupMembers(SealdSdk* sealdSdk, char* groupId, SealdStringArray* membersToRemove, char** errMsg);

/**
 * Renew the group's private key.
 * Can only be done by a group administrator.
 * Should be called after removing members from the group.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param groupId The group for which to renew the private key.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RenewGroupKey(SealdSdk* sealdSdk, char* groupId, char** errMsg);

/**
 * Add some existing group members to the group admins, and/or removes admin status from some existing group admins.
 * Can only be done by a group administrator.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param groupId The group for which to set admins.
 * @param addToAdmins The Seald IDs of existing group members to add as group admins.
 * @param removeFromAdmins The Seald IDs of existing group members to remove from group admins.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_SetGroupAdmins(SealdSdk* sealdSdk, char* groupId, SealdStringArray* addToAdmins, SealdStringArray* removeFromAdmins, char** errMsg);

/* EncryptionSession */

/**
 * Create an encryption session, and returns the associated SealdEncryptionSession instance,
 * with which you can then encrypt / decrypt multiple messages.
 * Warning : if you want to be able to retrieve the session later,
 * you must put your own Seald ID in the `recipients` argument.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param recipients The Seald IDs of users who should be able to retrieve this session.
 * @param useCache Whether or not to use the cache (if enabled globally). `1` to use cache, `0` to not use it.
 * @param result A pointer where to store the created SealdEncryptionSession instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_CreateEncryptionSession(SealdSdk* sealdSdk, SealdStringArray* recipients, int useCache, SealdEncryptionSession** result, char** errMsg);

/**
 * Retrieve an encryption session with the `messageId`, and returns the associated
 * SealdEncryptionSession instance, with which you can then encrypt / decrypt multiple messages.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param messageId The ID of the message belonging to the session to retrieve.
 * @param useCache Whether or not to use the cache (if enabled globally). `1` to use cache, `0` to not use it.
 * @param result A pointer where to store the retrieved SealdEncryptionSession instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RetrieveEncryptionSession(SealdSdk* sealdSdk, char* messageId, int useCache, SealdEncryptionSession** result, char** errMsg);

/**
 * Retrieve an encryption session from a Seald message, and returns the associated
 * SealdEncryptionSession instance, with which you can then encrypt / decrypt multiple messages.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param message Any message belonging to the session to retrieve.
 * @param useCache Whether or not to use the cache (if enabled globally). `1` to use cache, `0` to not use it.
 * @param result A pointer where to store the retrieved SealdEncryptionSession instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RetrieveEncryptionSessionFromMessage(SealdSdk* sealdSdk, char* message, int useCache, SealdEncryptionSession** result, char** errMsg);

/**
 * Retrieve an encryption session from a file path, and returns the associated
 * SealdEncryptionSession instance, with which you can then encrypt / decrypt multiple messages.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param filePath The path to an encrypted file belonging to the session to retrieve.
 * @param useCache Whether or not to use the cache (if enabled globally). `1` to use cache, `0` to not use it.
 * @param result A pointer where to store the retrieved SealdEncryptionSession instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RetrieveEncryptionSessionFromFile(SealdSdk* sealdSdk, char* filePath, int useCache, SealdEncryptionSession** result, char** errMsg);

/* Connectors */

/**
 * Get all the info for the given connectors to look for, updates the local cache of connectors,
 * and returns a SealdStringArray with the corresponding SealdIds. SealdIds are not de-duped and can appear for multiple connector values.
 * If one of the connectors is not assigned to a Seald user, this will return a ErrorGetSealdIdsUnknownConnector error,
 * with the details of the missing connector.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param connectorTypeValues A SealdConnectorTypeValueArray instance.
 * @param result A pointer where to store the SealdStringArray of Seald IDs of the users corresponding to these connectors.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_GetSealdIdsFromConnectors(SealdSdk* sealdSdk, SealdConnectorTypeValueArray* connectorTypeValues, SealdStringArray** result, char** errMsg);

/**
 * List all connectors known locally for a given Seald ID.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param sealdId The Seald ID for which to list connectors.
 * @param result A pointer where to store the SealdConnectorsArray instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_GetConnectorsFromSealdId(SealdSdk* sealdSdk, char* sealdId, SealdConnectorsArray** result, char** errMsg);

/**
 * Add a connector to the current identity.
 * If no preValidationToken is given, the connector will need to be validated before use.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param value The value of the connector to add.
 * @param connectorType The type of the connector.
 * @param preValidationToken Given by your server to authorize the adding of a connector.
 * @param result A pointer where to store the created SealdConnector instance.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_AddConnector(SealdSdk* sealdSdk, char* value, char* connectorType, SealdPreValidationToken* preValidationToken, SealdConnector** result, char** errMsg);

/**
 * Validate an added connector that was added without a preValidationToken.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param connectorId The ID of the connector to validate.
 * @param challenge The challenge.
 * @param result A pointer to a SealdConnector pointer where the result will be stored.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_ValidateConnector(SealdSdk* sealdSdk, char* connectorId, char* challenge, SealdConnector** result, char** errMsg);

/**
 * Remove a connector belonging to the current account.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param connectorId The ID of the connector to remove.
 * @param result A pointer to a SealdConnector pointer where the result will be stored.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RemoveConnector(SealdSdk* sealdSdk, char* connectorId, SealdConnector** result, char** errMsg);

/**
 * List connectors associated to the current account.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param result A pointer to a SealdConnectorsArray pointer where the result will be stored.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_ListConnectors(SealdSdk* sealdSdk, SealdConnectorsArray** result, char** errMsg);

/**
 * Retrieve a connector by its `connectorId`, then updates the local cache of connectors.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param connectorId The ID of the connector to retrieve.
 * @param result A pointer to a SealdConnector pointer where the result will be stored.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_RetrieveConnector(SealdSdk* sealdSdk, char* connectorId, SealdConnector** result, char** errMsg);

/* Reencrypt */

/**
 * Retrieve, re-encrypt, and add missing keys for a certain device.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param deviceId The ID of the device for which to re-rencrypt.
 * @param options A SealdMassReencryptOptions instance.
 * @param result A pointer to a SealdMassReencryptResponse instance, which will be populated with the number of re-encrypted keys, and the number of keys for which re-encryption failed.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_MassReencrypt(SealdSdk* sealdSdk, char* deviceId, SealdMassReencryptOptions options, SealdMassReencryptResponse* result, char** errMsg);

/**
 * List which of the devices of the current account are missing keys,
 * so you can call SealdSdk_MassReencrypt for them.
 *
 * @param sealdSdk The SealdSdk instance.
 * @param forceLocalAccountUpdate Whether to update the local account. `1` to update, `0` to not update.
 * @param result A pointer to a SealdDeviceMissingKeysArray*, in which to write the result.
 * @param errMsg A pointer to a char pointer where an error message will be stored in case of error.
 * @return Error code: `-1` if an error happened, `0` for success.
 */
int SealdSdk_DevicesMissingKeys(SealdSdk* sealdSdk, int forceLocalAccountUpdate, SealdDeviceMissingKeysArray** result, char** errMsg);

#endif // LIB_SEALD_SDK_H
