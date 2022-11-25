if [ "$1" = "h" ]; then
    printf 'profile <cf, iam, s3, ddb> action [params]\n'
fi

if [ "$2" = "iam" ]; then
    printf "IAM\n"
    if [ "$3" = "u" ]; then
        printf "checking $1 IAM users\n"
        aws --profile "$1" iam list-users
    fi
    if [ "$3" = "g" ]; then
        printf "checking $1 IAM groups\n"
        aws --profile "$1" iam list-groups
    fi
    if [ "$3" = "r" ]; then
        printf "checking $1 IAM roles\n"
        aws --profile "$1" iam list-roles
    fi
    if [ "$3" = "p" ]; then
        printf "checking $1 IAM policies\n"
        aws --profile "$1" iam list-policies
    fi
    if [ "$3" = "mfa" ]; then
        printf "checking $1 mfa on root user\n"
        aws --profile $1 iam list-virtual-mfa-devices
    fi
fi

if [ "$2" = "cf" ]; then
    printf "CloudFormation\n"
    if [ "$3" = "h" ]; then
        printf "l, ll, r, t\n"
    fi
    if [ "$3" = "l" ]; then
        printf "checking $1 CF stacks\n"
        aws --profile "$1" cloudformation list-stacks --stack-status-filter CREATE_COMPLETE
    fi
    if [ "$3" = "ll" ]; then
        printf "checking $1 CF stacks\n"
        aws --profile "$1" cloudformation list-stacks --stack-status-filter
    fi
    if [ "$3" = "r" ]; then
        printf "checking $1 resources\n"
        aws --profile $1 cloudformation list-stack-resources --stack-name $4
    fi
    if [ "$3" = "t" ]; then
        printf "checking $1 template\n"
        aws --profile $1 cloudformation get-template --stack-name $4
    fi
fi