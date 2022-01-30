# encryptor using vigenere or ceasar
<p>Simple tool to encrypt/decrypt using ceasar or vigenere encryption</p>

<h2>Examples</h2>
Let's say you have a input.txt file that you want to encrypt using the ceasar cipher.
<ol>
  <li>Choose an ASCII character. This is the key so don't tell anyone else. I choose: 'k'</li>
  <li>Think of an filename for the encrypted data. For example: input.txt.encrypted</li>
  <li> Now you can encrypt input.txt: <code>./encryptor ceasar encrypt input.txt input.txt.encrypted k</code></li>
  <li> To decrypt the file: <code>./encryptor ceasar decrypt input.txt.encrypted decrypted.txt k</code></li>
 </ol>

<p>This uses 'k' as the key. You can use any ASCII character as the key.</p>


<br>
<p>You can do something similar using the vigenere cipher:
<code>./encryptor vigenere decrypt encrypted.docx plain.docx keyfile.mp4</code>
  But this time, choose a file as the key instead of a single ASCII character. Make sure that this file is kept secret.
  </p>
Any file type can be used. Note that a larger key file is harder to crack, but this is limited to the input file size.
<br>

<h2>How does Ceasar encryption work?</h2>
<p>
With Ceasar encryption, you go byte per byte over the input file. For every byte, you add the value of the key. To decrypt, you subtract the key from the encrypted file. This type of encryption is very easy to crack, because there can only be 256 different keys and each byte is encoded with the same key.
</p>

<h2>How does Vigenere encryption work?</h2>
  <p>
    Vigenere is comparable with the Ceasar encryption, except that the key changes for every byte. Instead of applying one key to all the bytes, a keyfile is used where the bytes in the file are used for encryption and decryption. The first byte in the input is encrypted with the first byte of the keyfile, the second byte in the input is encrypted with the second byte of the keyfile and so on. When the input file is larger than the keyfile, the keyfile is repeated. This reduces safety because it means that some bytes are encrypted with the same values at a fixed distance. To solve this, the key file should be the same size or longer than the input file.
  </p>
 
  <h2>Caution!</h2>
  
  <p>This software probably has bugs and security flaws. It is not save to use this software to encrypt sensitive data. I am not responsible for any damages done by the software in this repository
  </p>
