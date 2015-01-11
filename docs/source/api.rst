PyGPGME API
###########

.. py:module:: gpgme


Context
=======


.. py:class:: Context

    Context are the most important object in gpgme.

    .. py:attribute:: armor

        Property indicating whether output should be ASCII-armored or
        not.

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

    .. py:method:: decrypt_verify(ciphertext, plaintext)

    .. py:method:: delete(key, allow_secret=False)

    .. py:method:: edit

    .. py:method:: encrypt(recipients, flags, plaintext, ciphertext)

       Encrypts plaintext so it can only be read by the given
       recipients.

       :param recipients: A list of Key objects. Only people in
         posession of the corresponding private key (for public key
         encryption) or passphrase (for symmetric encryption) will be
         able to decrypt the result.

       :param flags: ``ENCRYPT_*`` constants added together. See GPGME
         docs for details.

       :param plaintext: A file-like object opened for reading,
         containing the data to be encrypted.

       :param ciphertext: A file-like object opened for writing, where
         the encrypted data will be written. If the ``Context``'s
         :py:attr:`~Context.armor` property is ``False``, this file should
         be opened in binary mode.

    .. py:method:: encrypt_sign

    .. py:method:: export

    .. py:method:: genkey

    .. py:method:: get_key(fingerprint, secret=False)

        Finds a key with the given fingerprint (a string of hex digits) in
        the user's keyring.

        :param fingerprint: fingerprint of the key to look for

        :param secret: if ``True``, only private keys will be returned.

        If no key can be found, raises :py:exc:`GpgmeError`

        :return: a :py:class:`Key` instance.

    .. py:method:: import_

    .. py:method:: include_certs

    .. py:method:: keylist(query=None, secret=False)

        Searches for keys matching the given pattern(s).

        :param query: If ``None`` or not supplied, the
            :py:class:`KeyIter` fetches all available keys. If a
            string, it fetches keys matching the given pattern (such
            as a name or email address). If a sequence of strings, it
            fetches keys matching at least one of the given patterns.

        :param secret: If True, only secret keys will be returned
            (like 'gpg -K').

        :return: a :py:class:`KeyIter` instance, ready to be iterated
            for :py:class:`Key` objects

    .. py:attribute:: keylist_mode

        Property used to change the default behaviour of the key
        listing functions. The value in mode is a bitwise-or
        combination of one or multiple of the ``KEYLIST_MODE_*`` constants.

    .. py:method:: passphrase_cb

    .. py:method:: pinentry_mode

    .. py:method:: progress_cb

    .. py:attribute:: protocol

        Property used to get/set the protocol to be used.

        Accepted values are one of the ``PROTOCOL_*`` constants (below).

    .. py:method:: set_engine_info

    .. py:method:: set_locale

    .. py:method:: sign

    .. py:method:: signers

    .. py:method:: textmode

    .. py:method:: verify


Key
===

.. py:class:: Key

    .. py:attribute:: revoked

        True if the key has been revoked

    .. py:attribute:: expired

        True if the key is expired

    .. py:attribute:: disabled

        True if the key is disabled

    .. py:attribute:: invalid

       This is true if the key is invalid. This might have several
       reasons, for a example for the S/MIME backend, it will be set
       in during key listsing if the key could not be validated due to
       a missing certificates or unmatched policies.

    .. py:attribute:: can_encrypt

       This is true if the key (ie one of its subkeys) can be used for
       encryption.

    .. py:attribute:: can_sign

       This is true if the key (ie one of its subkeys) can be used to
       create data signatures.

    .. py:attribute:: can_certify

       This is true if the key (ie one of its subkeys) can be used to
       create key certificates.

    .. py:attribute:: secret

       This is true if the key is a secret key. Note, that this will
       always be true even if the corresponding subkey flag may be
       false (offline/stub keys). This is only set if a listing of
       secret keys has been requested or if
       ``KEYLIST_MODE_WITH_SECRET`` is active.

    .. py:attribute:: can_authenticate

       This is true if the key (ie one of its subkeys) can be used for
       authentication.

    .. py:attribute:: protocol

       This is the protocol supported by this key.

    .. py:attribute:: issuer_serial

       If protocol is ``PROTOCOL_CMS``, then this is the issuer
       serial.

    .. py:attribute:: issuer_name

       If protocol is ``PROTOCOL_CMS``, then this is the issuer name.

    .. py:attribute:: chain_id

       If protocol is ``PROTOCOL_CMS``, then this is the chain ID,
       which can be used to built the certificate chain.

    .. py:attribute:: owner_trust

       If protocol is ``PROTOCOL_OpenPGP``, then this is the owner
       trust.

    .. py:attribute:: subkeys

       This is a list with the subkeys of the key. The first subkey in
       the list is the primary key and usually available.

    .. py:attribute:: uids

       This is a list with the user IDs of the key. The first user ID
       in the list is the main (or primary) user ID.

    .. py:attribute:: keylist_mode

        The keylist mode that was active when the key was retrieved.


Helper objects
==============

Stuff that's mostly used internally, but it's good to know it's there.

.. py:class:: KeyIter

    Iterable yielding :py:class:`Key` instances for keylist results.

.. py:data:: gpgme_version

    gpgme version string


.. py:class:: GenKeyResult
.. py:class:: GpgmeError
.. py:class:: ImportResult
.. py:class:: KeySig
.. py:class:: NewSignature
.. py:class:: Signature
.. py:class:: Subkey
.. py:class:: UserId



Constants
=========

Protocol selection
------------------


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

     [#missing-const]_ Special protocol for use with gpgme_op_spawn.

.. py:data:: PROTOCOL_UNKNOWN

     [#missing-const]_ Reserved for future extension. You may use this
     to indicate that the used protocol is not known to the
     application. Currently, GPGME does not accept this value in any
     operation, though, except for gpgme_get_protocol_name.


Key listing mode
----------------

- ``KEYLIST_MODE_LOCAL`` specifies that the local keyring should be
  searched for keys in the keylisting operation. This is the default.
- ``KEYLIST_MODE_EXTERN`` specifies that an external source should be
  searched for keys in the keylisting operation. The type of external
  source is dependant on the crypto engine used and whether it is
  combined with ``KEYLIST_MODE_LOCAL``. For example, it can be a
  remote keyserver or LDAP certificate server.
- ``KEYLIST_MODE_SIGS`` specifies that the key signatures should be
  included in the listed keys.
- [#missing-const]_ ``KEYLIST_MODE_SIG_NOTATIONS`` specifies that the signature
  notations on key signatures should be included in the listed
  keys. This only works if KEYLIST_MODE_SIGS is also enabled.
- [#missing-const]_ ``KEYLIST_MODE_WITH_SECRET`` returns information about the presence
  of a corresponding secret key in a public key listing. A public key
  listing with this mode is slower than a standard listing but can be
  used instead of a second run to list the secret keys. This is only
  supported for GnuPG versions >= 2.1.
- [#missing-const]_ ``KEYLIST_MODE_EPHEMERAL`` specifies that keys flagged as ephemeral
  are included in the listing.
- [#missing-const]_ ``KEYLIST_MODE_VALIDATE`` specifies that the backend should do key
  or certificate validation and not just get the validity information
  from an internal cache. This might be an expensive operation and is
  in general not useful. Currently only implemented for the S/MIME
  backend and ignored for other backends.


Encryption flags
----------------

.. py:data:: ENCRYPT_ALWAYS_TRUST

  Specifies that all the recipients in recp should be trusted, even if
  the keys do not have a high enough validity in the keyring. This
  flag should be used with care; in general it is not a good idea to
  use any untrusted keys.

.. py:data:: ENCRYPT_NO_ENCRYPT_TO

  [#missing-const]_ specifies that no
  default or hidden default recipients as configured in the crypto
  backend should be included. This can be useful for managing
  different user profiles.

.. py:data:: ENCRYPT_NO_COMPRESS

  [#missing-const]_ specifies that the
  plaintext shall not be compressed before it is encrypted. This is in
  some cases useful if the length of the encrypted message may reveal
  information about the plaintext.

.. py:data:: ENCRYPT_PREPARE

  [#missing-const]_

.. py:data:: ENCRYPT_EXPECT_SIGN

  [#missing-const]_ The ``ENCRYPT_PREPARE`` symbol is used with the UI
  Server protocol to prepare an encryption (i.e. sending the
  ``PREP_ENCRYPT`` command). With the ``ENCRYPT_EXPECT_SIGN`` symbol
  the UI Server is advised to also expect a sign command.



.. [#missing-const] This constant is defined by the gpgme library, but
                    is currently missing in pygpgme.
