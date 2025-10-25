using System;
using System.Windows.Forms;
using System.IO;

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

            if(!Directory.Exists(textBoxDestinationFilePath.Text))
            {
                labelStatus.Text = "Destination directory does not exist";
                return false;
            }

            return true;
        }

        private void buttonEncrypt_Click(object sender, EventArgs e)
        {
            labelStatus.Text = "Button \"Encrypt\" clicked";

            if (!ParametersValid())
            {
                return;
            }
        }
    }
}