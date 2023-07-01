using Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Material.Icons;

namespace AvaloniaFrontend.Design;

public sealed class DesignPageService : PageService
{
    public DesignPageService()
    {
        Pages.Add(typeof(DesignPageService), new PageData()
        {
            Name = "DesignPage",
            Icon = MaterialIconKind.PencilRuler.ToString(),
        });

        Pages.Add(typeof(string), new PageData()
        {
            Name = "String Page",
            Icon = MaterialIconKind.Wordpress.ToString(),
        });

        Pages.Add(typeof(int), new PageData()
        {
            Name = "Int Page"
        });

        Pages.Add(typeof(double), new PageData()
        {
            Name = "double Page"
        });

        Pages.Add(typeof(float), new PageData()
        {
            Name = "Float Page"
        });
    }
}
