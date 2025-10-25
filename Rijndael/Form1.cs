using System;
using System.Windows.Forms;
using System.IO;
using System.Text;
using AESBridge;

namespace Rijndael
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            toolTip.SetToolTip(textBoxPassword, "min 7, max 32 symbols");
        }

        private void buttonSelectSourceFile_Click(object sender, EventArgs e)
        {
            if (openSourceFileDialog.ShowDialog() == DialogResult.OK)
            {
                textBoxSourceFilePath.Text = openSourceFileDialog.FileName;
            }
        }

        private void buttonSelectDestinationFile_Click(object sender, EventArgs e)
        {
            if (saveDestinationFileDialog.ShowDialog() == DialogResult.OK)
            {
                textBoxDestinationFilePath.Text = saveDestinationFileDialog.FileName;
            }
        }

        private void linkLabelHelp_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try
            {
                var psi = new System.Diagnostics.ProcessStartInfo
                {
                    FileName = "https://github.com/DaniilGalahov",
                    UseShellExecute = true
                };
                System.Diagnostics.Process.Start(psi);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Cannot open link. " + ex.Message);
            }
        }

        private bool ParametersValid()
        {
            if (textBoxSourceFilePath.Text.Length == 0)
            {
                labelStatus.Text = "No source file path";
                return false;
            }

            if (!File.Exists(textBoxSourceFilePath.Text))
            {
                labelStatus.Text = "Source file does not exist";
                return false;
            }

            if (textBoxDestinationFilePath.Text.Length == 0)
            {
                labelStatus.Text = "No destination file path";
                return false;
            }

            if(!Directory.Exists(Path.GetDirectoryName(textBoxDestinationFilePath.Text)))
            {
                labelStatus.Text = "Destination directory does not exist";
                return false;
            }

            if(File.Exists(textBoxDestinationFilePath.Text))
            {
                labelStatus.Text = "Destination file already exist";
                return false;
            }

            if(textBoxPassword.Text.Length < 7)
            {
                labelStatus.Text = "Password too short";
                return false;
            }

            return true;
        }

        private void SetControlResponseTo(bool value)
        {
            buttonEncrypt.Enabled = value;
            buttonDecrypt.Enabled = value;
            textBoxSourceFilePath.Enabled = value;
            buttonSelectSourceFile.Enabled = value;
            textBoxDestinationFilePath.Enabled = value;
            buttonSelectDestinationFile.Enabled = value;
            textBoxPassword.Enabled = value;
            comboBoxEncryptionStandard.Enabled = value;
        }

        private void DisableControls()
        {
            SetControlResponseTo(false);
        }

        private void EnableControls()
        {
            SetControlResponseTo(true);
        }

        private void Encrypt()
        {
            DisableControls();

            labelStatus.Text = "Encryption started";

            Byte[] openData = File.ReadAllBytes(textBoxSourceFilePath.Text);
            Byte[] userKey = Encoding.UTF8.GetBytes(textBoxPassword.Text);
            Mode mode = (Mode)comboBoxEncryptionStandard.SelectedIndex;
            Byte[] encryptedData = AES.Encrypt(openData, userKey, mode);
            File.WriteAllBytes(textBoxDestinationFilePath.Text, encryptedData);

            labelStatus.Text = "Encryption finished";

            EnableControls();
        }

        private void Decrypt()
        {
            DisableControls();

            labelStatus.Text = "Decryption started";

            Byte[] encryptedData = File.ReadAllBytes(textBoxSourceFilePath.Text);
            Byte[] userKey = Encoding.UTF8.GetBytes(textBoxPassword.Text);
            Mode mode = (Mode)comboBoxEncryptionStandard.SelectedIndex;
            Byte[] openData = AES.Decrypt(encryptedData, userKey, mode);
            File.WriteAllBytes(textBoxDestinationFilePath.Text, openData);

            labelStatus.Text = "Decryption finished";

            EnableControls();
        }

        private void buttonEncrypt_Click(object sender, EventArgs e)
        {
            labelStatus.Text = "Button \"Encrypt\" clicked";

            if (!ParametersValid())
            {
                return;
            }

            labelStatus.Text = "Parameters valid";

            Encrypt();
        }

        private void buttonDecrypt_Click(object sender, EventArgs e)
        {
            labelStatus.Text = "Button \"Decrypt\" clicked";

            if (!ParametersValid())
            {
                return;
            }

            labelStatus.Text = "Parameters valid";

            Decrypt();
        }
    }
}