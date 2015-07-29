PyGPGME API
###########

.. py:module:: gpgme


Context
=======

.. py:class:: Context

    Configuration and internal state for cryptographic operations.

    This is the main class of :py:mod:`gpgme`. The constructor takes
    no arguments::

        ctx = gpgme.Context()

    .. py:attribute:: armor

        Property indicating whether output should be ASCII-armored or
        not. Used by :py:meth:`Context.encrypt`,
        :py:meth:`Context.encrypt_sign`, and :py:meth:`Context.sign`.

    .. py:method:: card_edit

    .. py:method:: decrypt(ciphertext, plaintext)

        Decrypts the ciphertext and writes out the plaintext.

        To decrypt data, you must have one of the recipients' private keys in
        your keyring (for public key encryption) or the passphrase (for
        symmetric encryption). If gpg finds the key but needs a passphrase to
        unlock it, the .passphrase_cb callback will be used to ask for it.

        :param ciphertext: A file-like object opened for reading,
            containing the encrypted data.

        :param plaintext: A file-like object opened for writing, where
            the decrypted data will be written.

        See also :py:meth:`Context.decrypt_verify` and
        :py:meth:`Context.encrypt`.

    .. py:method:: decrypt_verify(ciphertext, plaintext)

        Decrypt ciphertext and verify signatures.

        Like :py:meth:`Context.decrypt`, but also checks the signatures
        of the ciphertext.

        :return: A list of :py:class:`Signature` instances (one for each key
                 that was used in the signature). Note that you need to inspect
                 the return value to check whether the signatures are valid --
                 a syntactically correct but invalid signature does not raise
                 an error!

        See also :py:meth:`Context.encrypt_sign`.

    .. py:method:: delete(key, allow_secret=False)

    .. py:method:: edit

    .. py:method:: encrypt(recipients, flags, plaintext, ciphertext)

        Encrypts plaintext so it can only be read by the given recipients.

        :param recipients: A list of Key objects. Only people in possession of
            the corresponding private key (for public key encryption) or
            passphrase (for symmetric encryption) will be able to decrypt the
            result.

        :param flags: A bitwise OR combination of ``ENCRYPT_*`` constants.

        :param plaintext: A file-like object opened for reading, containing the
            data to be encrypted.

        :param ciphertext: A file-like object opened for writing, where the
            encrypted data will be written. If :py:attr:`Context.armor` is
            false then this file should be opened in binary mode.

        See also :py:meth:`Context.encrypt_sign` and :py:meth:`Context.decrypt`.

    .. py:method:: encrypt_sign(recipients, flags, plaintext, ciphertext)

        Encrypt and sign plaintext.

        Works like :py:meth:`Context.encrypt`, but the ciphertext is also
        signed using all keys listed in :py:attr:`Context.signers`.

        :return: A list of :py:class:`NewSignature` instances (one for each
            key in :py:attr:`Context.signers`).

        See also :py:meth:`Context.decrypt_verify`.

    .. py:method:: export

    .. py:method:: genkey(params, public=None, secret=None)

        Generate a new key pair.

        The functionality of this method depends on the crypto backend set
        via :py:attr:`Context.protocol`. This documentation only covers PGP/GPG
        (i.e. :py:data:`PROTOCOL_OpenPGP`).

        The generated key pair is automatically added to the key ring. Use
        :py:meth:`Context.set_engine_info` to configure the location of the
        key ring files.

        :param params: A string containing the parameters for key generation.
            The general syntax is as follows::

                <GnupgKeyParms format="internal">
                    Key-Type: RSA
                    Key-Length: 2048
                    Name-Real: Jim Joe
                    Passphrase: secret passphrase
                    Expire-Date: 0
                </GnupgKeyParms>

            For a detailed listing of the available options please refer to the
            `GPG key generation documentation`_.

        :param public: Must be ``None``.

        :param secret: Must be ``None``.

        :return: An instance of :py:class:`gpgme.GenkeyResult`.

    .. py:method:: get_key(fingerprint, secret=False)

        Finds a key with the given fingerprint (a string of hex digits) in
        the user's keyring.

        :param fingerprint: Fingerprint of the key to look for

        :param secret: If true, only private keys will be returned.

        If no key can be found, raises :py:exc:`GpgmeError`.

        :return: A :py:class:`Key` instance.

    .. py:method:: import_

    .. py:method:: include_certs

    .. py:method:: keylist(query=None, secret=False)

        Searches for keys matching the given pattern(s).

        :param query: If ``None`` or not supplied, the :py:class:`KeyIter`
            fetches all available keys. If a string, it fetches keys matching
            the given pattern (such as a name or email address). If a sequence
            of strings, it fetches keys matching at least one of the given
            patterns.

        :param secret: If true, only secret keys will be returned.

        :return: A :py:class:`KeyIter` instance.

    .. py:attribute:: keylist_mode

        Default key listing behavior.

        Controls which keys :py:meth:`Context.keylist` returns. The value is a
        bitwise OR combination of one or multiple of the ``KEYLIST_MODE_*``
        constants. Defaults to :py:data:`KEYLIST_MODE_LOCAL`.

    .. py:method:: passphrase_cb

    .. py:method:: pinentry_mode

    .. py:method:: progress_cb

    .. py:attribute:: protocol

        The protocol used for talking to the backend. Accepted values are one
        of the ``PROTOCOL_*`` constants.

    .. py:method:: set_engine_info(protocol, executable, config_dir)

        Configure a crypto backend.

        Updates the configuration of the crypto backend for the given protocol.
        If this function is used then it must be called before any crypto
        operation is performed on the context.

        :param protocol: One of the ``PROTOCOL_*`` constants specifying which
            crypto backend is to be configured. Note that this does not change
            which crypto backend is actually used, see
            :py:attr:`Context.protocol` for that.

        :param executable: The path to the executable implementing the
            protocol. If ``None`` then the default will be used.

        :param config_dir: The path of the configuration directory of the crypto
            backend. If ``None`` then the default will be used.

    .. py:method:: set_locale

    .. py:method:: sign(plaintext, signed, mode=gpgme.SIG_MODE_NORMAL)

        Sign plaintext to certify and timestamp it.

        The plaintext is signed using all keys listed in
        :py:attr:`Context.signers`.

        :param plaintext: A file-like object opened for reading, containing
            the plaintext to be signed.

        :param signed: A file-like object opened for writing, where the
            signature data will be written. The signature data may contain the
            plaintext or not, see the ``mode`` parameter. If
            :py:attr:`Context.armor` is false and ``mode`` is not
            :py:data:`SIG_MODE_CLEAR` then the file should be opened in binary
            mode.

        :param mode: One of the ``SIG_MODE_*`` constants.

        :return: A list of :py:class:`NewSignature` instances (one for each
            key in :py:attr:`Context.signers`).

    .. py:attribute:: signers

        List of :py:class:`Key` instances used for signing with
        :py:meth:`sign` and :py:meth:`encrypt_sign`.

    .. py:method:: textmode

    .. py:method:: verify(signature, signedtext, plaintext)

        Verify signature(s) and extract plaintext.

        ``signature`` is a file-like object opened for reading, containing the
        signature data.

        If ``signature`` is a normal or cleartext signature (i.e. created using
        :py:data:`SIG_MODE_NORMAL` or :py:data:`SIG_MODE_CLEAR`) then
        ``signedtext`` must be ``None`` and ``plaintext`` a file-like object
        opened for writing that will contain the extracted plaintext.

        If ``signature`` is a detached signature (i.e. created using
        :py:data:`SIG_MODE_DETACHED`) then ``signedtext`` should contain a
        file-like object opened for reading containing the signed text and
        ``plaintext`` must be ``None``.

        :return: A list of :py:class:`Signature` instances (one for each key
            that was used in ``signature``). Note that you need to inspect the
            return value to check whether the signatures are valid -- a
            syntactically correct but invalid signature does not raise an
            error!

.. _`GPG key generation documentation`: https://www.gnupg.org/documentation/manuals/gnupg/Unattended-GPG-key-generation.html


GenkeyResult
============

.. py:class:: GenkeyResult

    Key generation result.

    Instances of this class are usually obtained as the return value
    of :py:meth:`Context.genkey`.

    .. py:attribute:: fpr

        String containing the fingerprint of the generated key. If both a
        primary and a subkey were generated then this is the fingerprint of
        the primary key. For crypto backends that do not provide key
        fingerprints this is ``None``.

    .. py:attribute:: primary

        True if a primary key was generated.

    .. py:attribute:: sub

        True if a sub key was generated.


Key
===

.. py:class:: Key

    .. py:attribute:: revoked

        True if the key has been revoked.

    .. py:attribute:: expired

        True if the key has expired.

    .. py:attribute:: disabled

        True if the key is disabled.

    .. py:attribute:: invalid

       True if the key is invalid. This might have several reasons. For
       example, for the S/MIME backend it will be set during key listing if the
       key could not be validated due to a missing certificates or unmatched
       policies.

    .. py:attribute:: can_encrypt

       True if the key (i.e. one of its subkeys) can be used for encryption.

    .. py:attribute:: can_sign

       True if the key (i.e. one of its subkeys) can be used to create
       signatures.

    .. py:attribute:: can_certify

       True if the key (i.e. one of its subkeys) can be used to create key
       certificates.

    .. py:attribute:: secret

       True if the key is a secret key. Note that this will always be true even
       if the corresponding subkey flag may be false (offline/stub keys). This
       is only set if a listing of secret keys has been requested or if
       :py:data:`KEYLIST_MODE_WITH_SECRET` is active.

    .. py:attribute:: can_authenticate

       True if the key (i.e. one of its subkeys) can be used for
       authentication.

    .. py:attribute:: protocol

       The protocol supported by this key. See the ``PROTOCOL_*`` constants.

    .. py:attribute:: issuer_serial

       If :py:attr:`Key.protocol` is :py:data:`PROTOCOL_CMS` then this is the
       issuer serial.

    .. py:attribute:: issuer_name

       If :py:attr:`Key.protocol` is :py:data:`PROTOCOL_CMS` then this is the
       issuer name.

    .. py:attribute:: chain_id

       If :py:attr:`Key.protocol` is :py:data:`PROTOCOL_CMS` then this is the
       chain ID, which can be used to built the certificate chain.

    .. py:attribute:: owner_trust

       If :py:attr:`Key.protocol` is :py:data:`PROTOCOL_OpenPGP` then this is
       the owner trust.

    .. py:attribute:: subkeys

       List of the key's subkeys as instances of :py:class:`Subkey`. The first
       subkey in the list is the primary key and usually available.

    .. py:attribute:: uids

       List of the key's user IDs as instances of :py:class:`UserId`. The first
       user ID in the list is the main (or primary) user ID.

    .. py:attribute:: keylist_mode

        The keylist mode that was active when the key was retrieved. See
        :py:attr:`Context.keylist_mode`.


NewSignature
============

.. py:class:: NewSignature

    Data for newly created signatures.

    Instances of this class are usually obtained as the result value of
    :py:meth:`Context.sign` or :py:meth:`Context.encrypt_sign`.


Signature
=========

.. py:class:: Signature

    Signature verification data.

    Instances of this class are usually obtained as the return value of
    :py:meth:`Context.verify` or :py:meth:`Context.decrypt_verify`.

    .. py:attribute:: exp_timestamp

        Expiration timestamp of the signature, or 0 if the signature does
        not expire.

    .. py:attribute:: fpr

        Fingerprint string.

    .. py:attribute:: notations

        A list of notation data in the form of tuples ``(name, value)``.

    .. py:attribute:: status

        If an error occurred during verification (for example because the
        signature is not valid) then this attribute contains a corresponding
        :py:class:`GpgmeError` instance. Otherwise it is ``None``.

    .. py:attribute:: summary

        A bit array encoded as an integer containing general information
        about the signature. Combine this value with one of the ``SIGSUM_*``
        constants using bitwise AND.

    .. py:attribute:: timestamp

        Creation timestamp of the signature.

    .. py:attribute:: validity

        Validity of the signature. See :py:attr:`Signature.validity_reason`.

    .. py:attribute:: validity_reason

        If a signature is not valid this may provide a reason why. See
        :py:attr:`Signature.validity`.

    .. py:attribute:: wrong_key_usage

        True if the key was not used according to its policy.


Helper Objects
==============

Stuff that's mostly used internally, but it's good to know it's there.

.. py:class:: KeyIter

    Iterable yielding :py:class:`Key` instances for keylist results.

.. py:data:: gpgme_version

    Version string of libgpgme used to build this module.

.. py:class:: GpgmeError
.. py:class:: ImportResult
.. py:class:: KeySig
.. py:class:: Subkey
.. py:class:: UserId



Constants
=========

Protocol Selection
------------------

The following constants can be used as value for :py:attr:`Context.protocol`.
They are also returned via :py:attr:`Key.protocol`.

.. py:data:: PROTOCOL_OpenPGP

    This specifies the OpenPGP protocol.

.. py:data:: PROTOCOL_CMS

    This specifies the Cryptographic Message Syntax.

.. py:data:: PROTOCOL_ASSUAN

     [#missing-const]_ Under development. Please ask on
     gnupg-devel@gnupg.org for help.

.. py:data:: PROTOCOL_G13

     [#missing-const]_ Under development. Please ask on
     gnupg-devel@gnupg.org for help.

.. py:data:: PROTOCOL_UISERVER

     [#missing-const]_ Under development. Please ask on
     gnupg-devel@gnupg.org for help.

.. py:data:: PROTOCOL_SPAWN

     [#missing-const]_ Special protocol for use with ``gpgme_op_spawn``.

.. py:data:: PROTOCOL_UNKNOWN

     [#missing-const]_ Reserved for future extension. You may use this to
     indicate that the used protocol is not known to the application.
     Currently, GPGME does not accept this value in any operation, though,
     except for ``gpgme_get_protocol_name``.


Key Listing Mode
----------------

Bitwise OR combinations of the following constants can be used as values for
:py:attr:`Context.keylist_mode`.

.. py:data:: KEYLIST_MODE_LOCAL

    Specifies that the local keyring should be searched. This is the default.

.. py:data:: KEYLIST_MODE_EXTERN

    Specifies that an external source should be searched. The type of external
    source is dependant on the crypto engine used and whether it is combined
    with :py:data:`KEYLIST_MODE_LOCAL`. For example, it can be a remote
    keyserver or LDAP certificate server.

.. py:data:: KEYLIST_MODE_SIGS

    Specifies that the key signatures should be included in the listed keys.

.. py:data:: KEYLIST_MODE_SIG_NOTATIONS

    [#missing-const]_ Specifies that the signature notations on key signatures
    should be included in the listed keys. This only works if
    :py:data:`KEYLIST_MODE_SIGS` is also enabled.

.. py:data:: KEYLIST_MODE_WITH_SECRET

    [#missing-const]_ Returns information about the presence of a corresponding
    secret key in a public key listing. A public key listing with this mode is
    slower than a standard listing but can be used instead of a second run to
    list the secret keys. This is only supported for GnuPG versions >= 2.1.

.. py:data:: KEYLIST_MODE_EPHEMERAL

    [#missing-const]_ Specifies that keys flagged as ephemeral are included in
    the listing.

.. py:data:: KEYLIST_MODE_VALIDATE

    [#missing-const]_ Specifies that the backend should do key or certificate
    validation and not just get the validity information from an internal
    cache. This might be an expensive operation and is in general not useful.
    Currently only implemented for the S/MIME backend and ignored for other
    backends.


Encryption Flags
----------------

Bitwise OR combinations of the following constants can be used for the
``flags`` parameter of :py:meth:`Context.encrypt` and
:py:meth:`Context.encrypt_sign`.

.. py:data:: ENCRYPT_ALWAYS_TRUST

  Specifies that all the recipients in recp should be trusted, even if
  the keys do not have a high enough validity in the keyring. This
  flag should be used with care; in general it is not a good idea to
  use any untrusted keys.

.. py:data:: ENCRYPT_NO_ENCRYPT_TO

  [#missing-const]_ Specifies that no default or hidden default recipients as
  configured in the crypto backend should be included. This can be useful for
  managing different user profiles.

.. py:data:: ENCRYPT_NO_COMPRESS

  [#missing-const]_ Specifies that the plaintext shall not be compressed before
  it is encrypted. This is in some cases useful if the length of the encrypted
  message may reveal information about the plaintext.

.. py:data:: ENCRYPT_PREPARE

  [#missing-const]_ Used with the UI Server protocol to prepare an encryption.

.. py:data:: ENCRYPT_EXPECT_SIGN

  [#missing-const]_ Used with the UI Server protocol to advise the UI server to
  expect a sign command.


Signing Modes
-------------

The following constants can be used for the ``mode`` parameter of
:py:meth:`Context.sign`.

.. py:data:: SIG_MODE_NORMAL

    A normal signature is made, the output includes the plaintext and the
    signature. :py:attr:`Context.armor` is respected.

.. py:data:: SIG_MODE_DETACHED

    A detached signature is created. :py:attr:`Context.armor` is respected.

.. py:data:: SIG_MODE_CLEAR

    A cleartext signature is created. :py:attr:`Context.armor` is ignored.


Signature Verification
----------------------

The following bit masks can be used to extract individual bits from
:py:attr:`Signature.summary` using bitwise AND.

.. py:data:: SIGSUM_VALID

    The signature is fully valid.

.. py:data:: SIGSUM_GREEN

    The signature is good but one might want to display some extra information.
    Check the other bits.

.. py:data:: SIGSUM_RED

    The signature is bad. It might be useful to check other bits and display
    more information, i.e. a revoked certificate might not render a signature
    invalid when the message was received prior to the cause for the
    revocation.

.. py:data:: SIGSUM_KEY_REVOKED

    The key or at least one certificate has been revoked.

.. py:data:: SIGSUM_KEY_EXPIRED

    The key or one of the certificates has expired.

.. py:data:: SIGSUM_SIG_EXPIRED

    The signature has expired.

.. py:data:: SIGSUM_KEY_MISSING

    Can’t verify due to a missing key or certificate.

.. py:data:: SIGSUM_CRL_MISSING

    The certificate revocation list (or an equivalent mechanism) is not
    available.

.. py:data:: SIGSUM_CRL_TOO_OLD

    The available certificate revocation list is too old.

.. py:data:: SIGSUM_BAD_POLICY

    A policy requirement was not met.

.. py:data:: SIGSUM_SYS_ERROR

    A system error occured.


.. [#missing-const] This constant is defined by the gpgme library, but
                    is currently missing in pygpgme.
